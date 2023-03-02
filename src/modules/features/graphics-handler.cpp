#include "graphics-handler.hpp"

// required includes
#include "../modules-manager.hpp"

// ImGui headers
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

namespace modules {
    namespace features {
        std::vector<std::function<void()>> graphics_handler::m_callbacks;

        graphics_handler::graphics_handler(modules_manager *context)
            : base_module(context, "graphics handler") {
            m_graphics = m_context->get_hooks().get_hook<hooks::graphics_hook>("graphics hook");
        }

        graphics_handler::~graphics_handler() = default;

        void graphics_handler::start() {
            m_graphics->callback.bind_callback(&graphics_handler::present, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        }

        void graphics_handler::update() {

        }

        HRESULT graphics_handler::present(IDXGISwapChain *pSwapChain,
                                          UINT SyncInterval,
                                          UINT Flags,
                                          bool& is_init) {
            if (!m_initialized) {
                ImGui::CreateContext();

                ImGuiIO& io = ImGui::GetIO();
                ImGui_ImplWin32_Init(m_graphics->get_current_hwnd());
                ImGui_ImplDX11_Init(m_graphics->get_device(), m_graphics->get_context());

                m_initialized = true;
            }

            if (m_open) {
                ImGui_ImplDX11_NewFrame();
                ImGui_ImplWin32_NewFrame();

                ImGui::NewFrame();
                {
                    if (ImGui::Begin("Hello"))
                    {
                        for (auto& item : m_callbacks) {
                            item();
                        }
                    }
                    ImGui::End();
                }
                ImGui::EndFrame();
                ImGui::Render();

                m_graphics->get_context()->OMSetRenderTargets(1, m_graphics->get_rtv(), NULL);
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
            }

            return S_OK;
        }

        bool graphics_handler::is_initialized() {
            return m_initialized;
        }

        void graphics_handler::toggle_menu() {
            m_open = !m_open;
        }
    } // modules
} // features