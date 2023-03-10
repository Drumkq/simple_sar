#pragma once

#include "../../base-hook.hpp"
#include "../../../utils/callbacks/callback.hpp"

#include <windows.h>

namespace hooks {
    class wndproc_hook final : public base_hook {
    public:
        wndproc_hook();

        void hook() override;
        void unhook() override;

        void rehook(HWND hwnd);

        static utils::callback<LRESULT, LRESULT(WNDPROC original_wndproc, const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)> callback;

    private:
        static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        static WNDPROC m_original_wndproc;

        HWND m_hwnd;
    };
}
