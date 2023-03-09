#include "wndproc-hook.hpp"

#include <spdlog/spdlog.h>

namespace hooks {
    WNDPROC wndproc_hook::m_original_wndproc;
    utils::callback<LRESULT, LRESULT(WNDPROC original_wndproc, const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)> wndproc_hook::callback;

    wndproc_hook::wndproc_hook()
        : base_hook("wndproc hook", true),
        m_hwnd(GetForegroundWindow()) {

    }

    void wndproc_hook::hook() {
        if (!m_hooked && m_hwnd != 0x0) {
            m_original_wndproc = (WNDPROC)SetWindowLongPtr(m_hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

            if (!m_original_wndproc) {
                m_hooked = false;
            }
            else {
                m_hooked = true;
            }
        }
    }

    void wndproc_hook::unhook() {
        if (m_hooked && m_original_wndproc) {
            SetWindowLongPtr(m_hwnd, GWLP_WNDPROC, (LONG_PTR)m_original_wndproc);
            m_hooked = false;
        }
    }

    void wndproc_hook::rehook(HWND hwnd) {
        m_hwnd = hwnd;

        hook();
    }

    LRESULT wndproc_hook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (callback.is_bind()) {
            return callback.call(m_original_wndproc, hWnd, uMsg, wParam, lParam);
        }

        return CallWindowProc(m_original_wndproc, hWnd, uMsg, wParam, lParam);
    }
} // hooks