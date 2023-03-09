#pragma once

#include <list>
#include <memory>

#include "base-hook.hpp"

namespace hooks {
    class hook_manager final {
    public:
        explicit hook_manager(std::list<std::shared_ptr<base_hook>> hooks);

        void hook_all();
        void unhook_all();

        template<class T>
        std::shared_ptr<T> get_hook(const char* name) {
            for (auto& hook : m_hooks) {
                if (strcmp(hook->name, name) == EXIT_SUCCESS) {
                    return std::dynamic_pointer_cast<T>(hook);
                }
            }

            return nullptr;
        }

    private:
        std::list<std::shared_ptr<base_hook>> m_hooks;
    };
}
