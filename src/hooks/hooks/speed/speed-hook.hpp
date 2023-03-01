#pragma once

#include "../../base-hook.hpp"
#include "../../../memory/buffers/runtime-buffer.hpp"

namespace hooks {
    class speed_hook : public base_hook {
    public:
        speed_hook();

        void hook() override;
        void unhook() override;

    private:
        runtime_buffer m_speed_1;
        runtime_buffer m_speed_2;

        uintptr_t m_speed_1_addr;
        uintptr_t m_speed_2_addr;
    };
}
