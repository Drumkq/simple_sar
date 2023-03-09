#include "player-hook.hpp"
#include "../../../memory/patcher/trampoline-patcher.hpp"

#include <spdlog/spdlog.h>

#include <iostream>

namespace hooks {
    uint64_t player_hook::m_player;
    player_hook::_sub_180FD03D0 player_hook::m_original;

    player_hook::player_hook() : base_hook("player hook", true) {
        spdlog::info("[hook] player hook loaded");
    }

    void player_hook::unhook() {
        m_tramp_buffer.restore();
    
        m_hooked = false;
    }

    void player_hook::hook() {
        _sub_180FD03D0 o_fn = (_sub_180FD03D0)(((uintptr_t)GetModuleHandle("GameAssembly.dll") + 0xEBE6E0));
        m_original = (_sub_180FD03D0)patcher::trampoline64((uintptr_t)&sub_180FD03D0, (uintptr_t)o_fn, 20u, m_tramp_buffer);

        m_hooked = true;
    }

    char __fastcall player_hook::sub_180FD03D0(__int64 a1, char a2)
    {
        m_player = *(uint64_t*)(a1 + 0x48);

        return m_original(a1, a2);
    }
} // hooks