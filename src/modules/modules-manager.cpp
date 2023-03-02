#include "modules-manager.hpp"

namespace modules {
    modules_manager::modules_manager(hooks::hook_manager &hooks)
        : m_hooks(hooks) {

    }

    modules_manager::~modules_manager() = default;

    void modules_manager::start() {
        for (auto& element : m_modules) {
            element->start();
        }
    }

    void modules_manager::update() {
        for (auto& element : m_modules) {
            element->update();
        }
    }
} // modules