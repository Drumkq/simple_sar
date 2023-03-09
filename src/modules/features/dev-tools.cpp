#include "dev-tools.hpp"

// required includes
#include "../modules-manager.hpp"
#include "../../utils/game-structs/sar_player.hpp"

// additional includes
#include <spdlog/spdlog.h>
#include <imgui/imgui.h>
#include <Windows.h>

#include <iostream>

namespace modules {
    namespace features {
        dev_tools::dev_tools(modules::modules_manager *context)
            : base_module(context, "dev tools"){

        }

        void dev_tools::start() {
#ifdef _DEBUG
            m_player = m_context->get_hooks().get_hook<hooks::player_hook>("player hook");
#endif
        }

        void dev_tools::update() {
#ifdef _DEBUG

#endif
        }

        void dev_tools::render() {
#ifdef _DEBUG
            if (ImGui::BeginChild(1, { 0, 0 }, true)) {
                ImGui::Text("Player: %p", m_player->get_player());
                if (ImGui::Button("Copy player address")) {
                    std::stringstream stream;
                    stream << std::hex << m_player->get_player();
                    std::string result(stream.str());

                    copy_to_clipboard(result.data(), result.size() + 1);
                }

                auto player = game_structs::sar_player(m_player->get_player());
                if (player.is_valid()) {
                    ImGui::Text("Health: %f", player.get_health());
                    ImGui::Text("Armor: %f", player.get_armor());
                    ImGui::Text("Position: { %f %f }", player.get_x_position(), player.get_y_position());
                    ImGui::Text("Current move state: %i", *player.get_move_state());
                    ImGui::Text("Current slot id: %i", player.get_current_slot_id());
                    ImGui::Text("Current weapon address: %p", player.get_weapon_address());
                    if (ImGui::Button("Copy weapon address")) {
                        std::stringstream stream;
                        stream << std::hex << player.get_weapon_address();
                        std::string result(stream.str());

                        copy_to_clipboard(result.data(), result.size() + 1);
                    }
                }

                ImGui::EndChild();
            }
#endif
        }

        void dev_tools::copy_to_clipboard(char* value, size_t length)
        {
            HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, length);
            memcpy(GlobalLock(hMem), value, length);
            GlobalUnlock(hMem);

            OpenClipboard(0);
            EmptyClipboard();
            SetClipboardData(CF_TEXT, hMem);
            CloseClipboard();
        }
    } // modules
} // features