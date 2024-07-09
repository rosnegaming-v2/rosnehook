/*
 * common.hpp
 *
 *  Created on: Dec 5, 2016
 *      Author: nullifiedcat
 */

#pragma once

#include "config.h"

#include <vector>
#include <string>
#include <array>
#include <mutex>
#include <cmath>
#include <memory>
#include <fstream>
#include <unordered_map>
#include <algorithm>

#include <unistd.h>
#include <link.h>
#include <sys/sysinfo.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>

#include "timer.hpp"

#include "core/macros.hpp"
#if ENABLE_VISUALS
#include <visual/colors.hpp>
#include <visual/drawing.hpp>
#endif

#include "core/offsets.hpp"
#include <entitycache.hpp>
#include <enums.hpp>
#include "velocity.hpp"
#include "globals.hpp"
#include <helpers.hpp>
#include "playerlist.hpp"
#include <core/interfaces.hpp>
#include <localplayer.hpp>
#include <conditions.hpp>
#include <core/logging.hpp>
#include "playerresource.hpp"
#include "sdk/usercmd.hpp"
#include "trace.hpp"
#include <core/cvwrapper.hpp>
#include "core/netvars.hpp"
#include "core/vfunc.hpp"
#include "hooks.hpp"
#include <prediction.hpp>
#include <itemtypes.hpp>
#include <chatstack.hpp>
#include "pathio.hpp"
#include "ipc.hpp"
#include "tfmm.hpp"
#include "hooks/HookedMethods.hpp"
#include "classinfo/classinfo.hpp"
#include "crits.hpp"
#include "textmode.hpp"
#include "core/sharedobj.hpp"
#include "init.hpp"
#include "reclasses/reclasses.hpp"
#include "HookTools.hpp"
#include "bytepatch.hpp"

#include "copypasted/Netvar.h"
#include "copypasted/CSignature.h"

#include <core/sdk.hpp>

#define _FASTCALL __attribute__((fastcall))
#define STRINGIFY(x) #x

#define SUPER_VERBOSE_DEBUG false
#if SUPER_VERBOSE_DEBUG
#define SVDBG(...) logging::Info(__VA_ARGS__)
#else
#define SVDBG(...)
#endif

#ifndef DEG2RAD
#define DEG2RAD(x) (float) (x) * (PI / 180.0f)
#endif

#define GET_RENDER_CONTEXT (g_IMaterialSystem->GetRenderContext())