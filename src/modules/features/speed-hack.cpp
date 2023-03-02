#include "speed-hack.hpp"

// required includes
#include "../modules-manager.hpp"

// additional includes
#include <spdlog/spdlog.h>

#include <imgui/imgui.h>

namespace modules {
    namespace features {
        speed_hack::speed_hack(modules_manager *context)
            : base_module(context, "speed hack"), base_renderable() {
            spdlog::info("[module] speed hack loaded successfully!");
            m_speed_hook = m_context->get_hooks().get_hook<hooks::speed_hook>("speed hook");
        }

        speed_hack::~speed_hack() = default;

        void speed_hack::update() {
            m_enable ? m_speed_hook->hook() : m_speed_hook->unhook();
        }

        void speed_hack::start() {

        }

        void speed_hack::render() {
            ImGui::Checkbox("Speed hack", &m_enable);
        }
    } // modules
} // features