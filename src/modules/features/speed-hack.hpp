#pragma once

// required includes
#include "../base-module.hpp"
#include <memory>

// required hooks includes
#include "../../hooks/hooks/speed/speed-hook.hpp"

namespace modules {
    namespace features {
        class speed_hack final : public base_module {
        public:
            speed_hack(struct modules_manager* context);
            ~speed_hack() override;

        protected:
            void update() override;
            void start() override;

        private:
            std::shared_ptr<hooks::speed_hook> m_speed_hook;
        };
    }
}
