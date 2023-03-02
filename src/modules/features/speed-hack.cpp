#include "speed-hack.hpp"

// required includes
#include "../modules-manager.hpp"
#include <windows.h>

// additional includes
#include <spdlog/spdlog.h>

namespace modules {
    namespace features {
        speed_hack::speed_hack(modules_manager *context)
            : base_module(context, "speed hack") {
            spdlog::info("[module] speed hack loaded successfully!");
            m_speed_hook = m_context->get_hooks().get_hook<hooks::speed_hook>("speed hook");
        }

        speed_hack::~speed_hack() = default;

        void speed_hack::update() {
            if (GetAsyncKeyState(0x5A) & 1) {
                m_speed_hook->toggle();
            }
        }

        void speed_hack::start() {

        }
    } // modules
} // features