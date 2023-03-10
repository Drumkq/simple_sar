#include "speed-hook.hpp"

#include "speed-sigs.hpp"
#include "../../../memory/scanners/pattern-scanner.hpp"
#include "../../../memory/memory-helper.hpp"

#include <spdlog/spdlog.h>

namespace hooks {
    speed_hook::speed_hook()
        : base_hook("speed hook"),
        m_speed_1_addr(scanners::find_pattern("GameAssembly.dll", signatures::speed_1_sig, signatures::speed_1_mask)),
        m_speed_2_addr(scanners::find_pattern("GameAssembly.dll", signatures::speed_2_sig, signatures::speed_2_mask)) {
        spdlog::info("[hook] speed hook loaded");
    }

    void speed_hook::hook() {
        if (!m_hooked) {
            memory_helper::nop_area(m_speed_1_addr, 7u, m_speed_1);
            memory_helper::nop_area(m_speed_2_addr, 7u, m_speed_2);

            m_hooked = true;
        }
    }

    void speed_hook::unhook() {
        if (m_hooked) {
            memory_helper::patch_area(m_speed_1);
            memory_helper::patch_area(m_speed_2);

            m_hooked = false;
        }
    }
} // hooks