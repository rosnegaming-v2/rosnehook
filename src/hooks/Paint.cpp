/*
 * Paint.cpp
 *
 *  Created on: Dec 31, 2017
 *      Author: nullifiedcat
 */

#include <settings/Bool.hpp>
#include "common.hpp"
#include "hitrate.hpp"
#include "hack.hpp"
#if ENABLE_VISUALS
#include "drawmgr.hpp"
#endif
#if !ENABLE_VISUALS
static Timer check_mm_ban{};
#endif
namespace hooked_methods
{
DEFINE_HOOKED_METHOD(Paint, void, IEngineVGui *this_, PaintMode_t mode)
{
    if (!isHackActive())
        return original::Paint(this_, mode);

    if (!g_IEngine->IsInGame())
        g_Settings.bInvalid = true;

    INetChannel *ch;
    ch = (INetChannel *) g_IEngine->GetNetChannelInfo();
    if (ch && !hooks::netchannel.IsHooked((void *) ch))
    {
        hooks::netchannel.Set(ch);
        hooks::netchannel.HookMethod(HOOK_ARGS(SendDatagram));
        hooks::netchannel.HookMethod(HOOK_ARGS(CanPacket));
        hooks::netchannel.HookMethod(HOOK_ARGS(SendNetMsg));
        hooks::netchannel.HookMethod(HOOK_ARGS(Shutdown));
        hooks::netchannel.Apply();
#if ENABLE_IPC
        ipc::UpdateServerAddress();
#endif
    }

    if (mode & PaintMode_t::PAINT_UIPANELS)
    {
        hitrate::Update();
#if ENABLE_IPC
        static Timer nametimer{};
        if (nametimer.test_and_set(10000) && ipc::peer)
            ipc::StoreClientData();

        static Timer ipc_timer{};
        if (ipc_timer.test_and_set(1000) && ipc::peer)
        {
            if (ipc::peer->HasCommands())
                ipc::peer->ProcessCommands();
            ipc::Heartbeat();
            ipc::UpdateTemporaryData();
        }
#endif
        if (!hack::command_stack().empty())
        {
            std::lock_guard<std::mutex> guard(hack::command_stack_mutex);
            g_IEngine->ClientCmd_Unrestricted(hack::command_stack().top().c_str());
            hack::command_stack().pop();
        }

#if ENABLE_TEXTMODE_STDIN
        static auto last_stdin = std::chrono::system_clock::from_time_t(0);
        auto ms                = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_stdin).count();
        if (ms > 500)
        {
            UpdateInput();
            last_stdin = std::chrono::system_clock::now();
        }
#endif
        // MOVED BACK because glez and imgui flicker in painttraveerse
#if ENABLE_IMGUI_DRAWING || ENABLE_GLEZ_DRAWING
        RenderCheatVisuals();
#endif
        // Call all paint functions
        EC::run(EC::Paint);
    }

#if ENABLE_TEXTMODE
    return;
#else
    return original::Paint(this_, mode);
#endif
}
} // namespace hooked_methods
