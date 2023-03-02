#pragma once

#include "../../base-hook.hpp"
#include "../../../utils/callbacks/callback.hpp"
#include "../../../memory/buffers/vmt-buffer.hpp"

#include <windows.h>
#include <d3d11.h>
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

namespace hooks {
    class graphics_hook final : public base_hook {
    public:
        graphics_hook();

        void hook() override;
        void unhook() override;

        static utils::callback<HRESULT, HRESULT(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags, bool& is_init)> callback;

        static HRESULT __stdcall present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

        ID3D11Device* get_device() {
            return m_device;
        }

        ID3D11DeviceContext* get_context() {
            return m_context;
        }

        ID3D11RenderTargetView** get_rtv() {
            return &m_rtv;
        }

        HWND get_current_hwnd() {
            return m_hwnd;
        }

    private:
        static graphics_hook* m_instance;

        ID3D11Device* m_device{};
        ID3D11DeviceContext* m_context{};
        ID3D11RenderTargetView* m_rtv{};
        ID3D11Texture2D* m_back_buffer{};

        HWND m_hwnd{};

        Present m_original_present{};

        vmt_buffer m_vmts;
    };
}
