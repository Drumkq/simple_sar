#include "warfog-hook.hpp"

#include "warfog-sigs.hpp"
#include "../../../memory/scanners/pattern-scanner.hpp"
#include "../../../memory/memory-helper.hpp"

#include <spdlog/spdlog.h>

namespace hooks {
    warfog_hook::warfog_hook()
        : base_hook("warfog hook"),
        m_warfog_address(scanners::find_pattern("GameAssembly.dll", signatures::warfog_1_sig, signatures::warfog_1_mask)),
        m_warfog_address_2(scanners::find_pattern("GameAssembly.dll", signatures::warfog_2_sig, signatures::warfog_2_mask)) {
        spdlog::info("[hook] warfog hook loaded");
    }

    void warfog_hook::hook() {
        if (!m_hooked) {
            memory_helper::nop_area(m_warfog_address, 7u, m_warfog_buffer);
            memory_helper::nop_area(m_warfog_address_2, 7u, m_warfog_buffer_2);

            m_hooked = true;
        }
    }

    void warfog_hook::unhook() {
        if (m_hooked) {
            memory_helper::patch_area(m_warfog_buffer);
            memory_helper::patch_area(m_warfog_buffer_2);

            m_hooked = false;
        }
    }
} // hooks