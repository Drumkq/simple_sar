#pragma once

#include "../../base-hook.hpp"
#include "../../../memory/buffers/runtime-buffer.hpp"

namespace hooks {
    class warfog_hook final : public base_hook {
    public:
        warfog_hook();

        void hook() override;
        void unhook() override;

    private:
        runtime_buffer m_warfog_buffer;
        runtime_buffer m_warfog_buffer_2;

        uintptr_t m_warfog_address;
        uintptr_t m_warfog_address_2;
    };
}
