#include "warfog-removable.hpp"

// required includes
#include "../modules-manager.hpp"

// additional includes
#include <spdlog/spdlog.h>
#include <imgui/imgui.h>

namespace modules {
    namespace features {
        warfog_removable::warfog_removable(modules_manager* context)
            : base_module(context, "warfog removable"), base_renderable() {
            spdlog::info("[module] warfog removable loaded successfully!");
            m_warfog_hook = m_context->get_hooks().get_hook<hooks::warfog_hook>("warfog hook");
        }

        warfog_removable::~warfog_removable() = default;

        void warfog_removable::update() {
            m_enable ? m_warfog_hook->hook() : m_warfog_hook->unhook();
        }

        void warfog_removable::start() {

        }

        void warfog_removable::render() {
            ImGui::Checkbox("War fog for players", &m_enable);
        }
    } // modules
} // features