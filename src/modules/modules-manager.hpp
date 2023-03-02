#pragma once

#include "base-module.hpp"
#include "../hooks/hook-manager.hpp"

#include <vector>
#include <memory>

namespace modules {
    class modules_manager {
    public:
        explicit modules_manager(hooks::hook_manager &hooks);
        ~modules_manager();

        void start();
        void update();

        hooks::hook_manager& get_hooks() {
            return m_hooks;
        }

        template<class T, class... Other>
        void add_module(modules_manager* context, Other... p) {
            m_modules.emplace_back(std::make_shared<T>(context, p...));
        }

        template<class T, class... Other>
        void add_module(Other... p) {
            add_module<T>(this, p...);
        }

        template<class T>
        std::shared_ptr<T> get_module(const char* name) {
            for (auto& module : m_modules) {
                if (strcmp(name, module->name) == EXIT_SUCCESS) {
                    return std::dynamic_pointer_cast<T>(module);
                }
            }

            return nullptr;
        }

    private:
        std::vector<std::shared_ptr<base_module>> m_modules;
        hooks::hook_manager& m_hooks;
    };
}
