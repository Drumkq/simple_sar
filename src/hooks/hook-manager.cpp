#include "hook-manager.hpp"

#include <utility>

namespace hooks {

    hook_manager::hook_manager(std::list<std::shared_ptr<base_hook>> hooks)
        : m_hooks(std::move(hooks)) {

    }

    void hook_manager::hook_all() {
        for (auto& hook : m_hooks) {
            if (hook->optional) {
                hook->hook();
            }
        }
    }

    void hook_manager::unhook_all() {
        for (auto& hook : m_hooks) {
            if (hook->is_hooked()) {
                hook->unhook();
            }
        }
    }
} // hooks