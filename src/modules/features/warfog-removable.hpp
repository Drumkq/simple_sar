#pragma once

// required includes
#include "../base-module.hpp"
#include "../base-renderable.hpp"
#include <memory>

// required hooks includes
#include "../../hooks/hooks/warfog/warfog-hook.hpp"

namespace modules {
    namespace features {
        class warfog_removable final : public base_module, base_renderable {
        public:
            warfog_removable(struct modules_manager* context);
            ~warfog_removable() override;

        protected:
            void update() override;
            void start() override;
            void render() override;

        private:
            std::shared_ptr<hooks::warfog_hook> m_warfog_hook;

            bool m_enable = false;
        };
    }
}
