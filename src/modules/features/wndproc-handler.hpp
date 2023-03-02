#pragma once

// required includes
#include "../modules-manager.hpp"
#include <windows.h>

// additional includes
#include <spdlog/spdlog.h>

namespace modules {
    namespace features {
        class wndproc_handler final : public base_module {
        public:
            wndproc_handler(modules_manager* context);
            ~wndproc_handler() override;

            void start() override;
            void update() override;

        private:
            LRESULT WndProcHandler(WNDPROC original_wndproc, const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        };
    }
}
