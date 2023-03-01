#pragma once

#include <list>
#include <memory>

#include "base-hook.hpp"

namespace hooks {
    class hook_manager {
    public:
        explicit hook_manager(std::list<std::shared_ptr<base_hook>> hooks);

        void hook_all();
        void unhook_all();

        template<class T>
        std::shared_ptr<T>& get_hook(const char* name) const {
            for (auto& hook : m_hooks) {
                if (strcmp(hook->name, name) == EXIT_SUCCESS) {
                    auto casted_hook = reinterpret_cast<T>(hook);
                    return casted_hook ? casted_hook : nullptr;
                }
            }
        }

    private:
        mutable std::list<std::shared_ptr<base_hook>> m_hooks;
    };
}
