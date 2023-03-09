#pragma once

#include "../../base-hook.hpp"
#include "../../../memory/buffers/trampoline-buffer.hpp"
#include <cstdint>

namespace hooks {
    class player_hook final : public base_hook {
        typedef char(__fastcall* _sub_180FD03D0)(__int64 a1, char a2);
    public:
        player_hook();
        ~player_hook() override = default;

        void unhook() override;
        void hook() override;

        uint64_t get_player() { return m_player; }

        static char __fastcall sub_180FD03D0(__int64 a1, char a2);

    private:
        static uint64_t m_player;
        static _sub_180FD03D0 m_original;
        trampoline_buffer m_tramp_buffer;
    };
}
