#include "wndproc-handler.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include <imgui/imgui_impl_win32.h>

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
            if (true & ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
            {
                return true;
            }
            return CallWindowProc(original_wndproc, hWnd, uMsg, wParam, lParam);
        }
    } // features
} // modules
