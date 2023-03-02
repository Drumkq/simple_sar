#pragma once

// required includes
#include "../base-module.hpp"
#include <functional>
#include <vector>
#include <memory>

// additional includes
#include "../../hooks/hooks/d3d11/graphics-hook.hpp"

namespace modules {
    namespace features {
        class graphics_handler final : public base_module {
        public:
            graphics_handler(modules_manager* context);
            ~graphics_handler() override;

            void update() override;
            void start() override;
            void toggle_menu();

            bool is_initialized();

            template<class T, class Mtd>
            static void add_render_callback(T* _this, Mtd&& mtd) {
                m_callbacks.emplace_back(std::bind(mtd, _this));
            }

        protected:
            HRESULT present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags, bool& is_init);

        private:
            std::shared_ptr<hooks::graphics_hook> m_graphics;
            bool m_initialized = false;
            static std::vector<std::function<void()>> m_callbacks;

            bool m_open = true;
        };
    }
}
