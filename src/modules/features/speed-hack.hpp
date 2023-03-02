#pragma once

// required includes
#include "../base-module.hpp"
#include "../base-renderable.hpp"
#include "graphics-handler.hpp"
#include <memory>

// required hooks includes
#include "../../hooks/hooks/speed/speed-hook.hpp"

namespace modules {
    namespace features {
        class speed_hack final : public base_module, base_renderable {
        public:
            speed_hack(struct modules_manager* context);
            ~speed_hack() override;

        protected:
            void update() override;
            void start() override;
            void render() override;

        private:
            std::shared_ptr<hooks::speed_hook> m_speed_hook;

            bool m_enable = false;
        };
    }
}
