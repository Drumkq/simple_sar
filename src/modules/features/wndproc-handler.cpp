#include "wndproc-handler.hpp"

#include "../../hooks/hooks/wndproc/wndproc-hook.hpp"

namespace modules {
    namespace features {
        wndproc_handler::wndproc_handler(modules::modules_manager *context)
            : base_module(context, "wndproc handler") {

        }

        wndproc_handler::~wndproc_handler() {

        }

        void wndproc_handler::start() {
            hooks::wndproc_hook::callback.bind_callback(&wndproc_handler::WndProcHandler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
        }

        void wndproc_handler::update() {

        }

        LRESULT wndproc_handler::WndProcHandler(WNDPROC original_wndproc, const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
            return CallWindowProc(original_wndproc, hWnd, uMsg, wParam, lParam);
        }
    } // features
} // modules
