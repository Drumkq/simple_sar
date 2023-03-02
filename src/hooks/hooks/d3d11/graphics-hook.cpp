#include "graphics-hook.hpp"

#include <iostream>

namespace hooks {
    utils::callback<HRESULT, HRESULT(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags, bool& is_init)> graphics_hook::callback;
    graphics_hook* graphics_hook::m_instance;

    graphics_hook::graphics_hook()
        : base_hook("graphics hook", true) {
        if (!m_instance) {
            m_instance = this;
        }
    }

    void graphics_hook::hook() {
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = GetForegroundWindow();
        sd.SampleDesc.Count = 1;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        IDXGISwapChain* swap_chain;
        ID3D11Device* device;

        const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        if (D3D11CreateDeviceAndSwapChain(
                NULL,
                D3D_DRIVER_TYPE_HARDWARE,
                NULL,
                0,
                feature_levels,
                2,
                D3D11_SDK_VERSION,
                &sd,
                &swap_chain,
                &device,
                nullptr,
                nullptr) == S_OK) {
            m_vmts.set_object((void*)swap_chain);
            m_original_present = (Present)m_vmts.update_method(&present, 8).old_method;
            swap_chain->Release();
            device->Release();
        }
    }

    void graphics_hook::unhook() {
        m_vmts.remove_methods();

        m_hooked = false;
    }

    HRESULT __stdcall graphics_hook::present(IDXGISwapChain* p_swap_chain, UINT SyncInterval, UINT Flags) {
        static bool init = false;

        if (!init) {
            if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&m_instance->m_device))) {
                m_instance->m_device->GetImmediateContext(&m_instance->m_context);
                m_instance->m_device->GetImmediateContext(&m_instance->m_context);

                DXGI_SWAP_CHAIN_DESC sd;
                p_swap_chain->GetDesc(&sd);

                m_instance->m_hwnd = sd.OutputWindow;

                ID3D11Texture2D* pBackBuffer;

                p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
                m_instance->m_device->CreateRenderTargetView(pBackBuffer, nullptr, &m_instance->m_rtv);
                pBackBuffer->Release();
            } else {
                return m_instance->m_original_present(p_swap_chain, SyncInterval, Flags);
            }

            init = true;

            m_instance->m_hooked = true;
        }

        if (callback.is_bind()) {
            callback.call(p_swap_chain, SyncInterval, Flags, init);
        }

        return m_instance->m_original_present(p_swap_chain, SyncInterval, Flags);
    }
} // hooks