#include "HookedMethods.hpp"
#include "CatBot.hpp"
#include "interfaces.hpp"
#include "ipc.hpp"

namespace hooked_methods
{
DEFINE_HOOKED_METHOD(ClientCmd_Unrestricted, void, IVEngineClient013 *_this, const char *command)
{
    if (ipc::peer && *hacks::catbot::requeue_if_ipc_bots_gte)
    {
        std::string command_str(command);

        if (command_str.length() >= 20 && command_str.substr(0, 7) == "connect")
        {
            unsigned int count_ipc = 0;

            if (command_str.substr(command_str.length() - 11, 11) == "matchmaking")
            {
                std::string server_ip = command_str.substr(8, command_str.length() - 20);

                auto &peer_mem = ipc::peer->memory;

                for (unsigned int i = 0; i < cat_ipc::max_peers; ++i)
                {
                    if (i != ipc::peer->client_id && !peer_mem->peer_data[i].free && peer_mem->peer_user_data[i].connected && peer_mem->peer_user_data[i].ingame.server)
                    {
                        std::string remote_server_ip(peer_mem->peer_user_data[i].ingame.server);
                        if (remote_server_ip == server_ip)
                            count_ipc++;
                    }
                }
            }

            if (count_ipc > 0 && count_ipc >= *hacks::catbot::requeue_if_ipc_bots_gte)
                return;
        }
    }

    original::ClientCmd_Unrestricted(_this, command);
}
} // namespace hooked_methods
