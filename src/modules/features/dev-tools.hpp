#pragma once

#include "../../hooks/hooks/player/player-hook.hpp"

// required includes
#include "../base-module.hpp"
#include "../base-renderable.hpp"

namespace modules {
    namespace features {
        class dev_tools final : public base_module, base_renderable {
        public:
            dev_tools(modules::modules_manager *context);
            ~dev_tools() override = default;

            void start() override;
            void update() override;
            void render() override;

        private:
            void copy_to_clipboard(char* value, size_t length);

        private:
            std::shared_ptr<hooks::player_hook> m_player;
        };
    }
}
