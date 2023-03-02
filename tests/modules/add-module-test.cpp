#include "gtest/gtest.h"

#include <modules/modules-manager.hpp>

class my_module : public modules::base_module {
public:
    explicit my_module(modules::modules_manager* context)
        : modules::base_module(context, "my module"){

    }

    ~my_module() override = default;

    void start() override {

    }

    void update() override {

    }
};

TEST(modules_manager, add_module) {
    hooks::hook_manager hooks({});
    modules::modules_manager manager(hooks);

    manager.add_module<my_module>();
    manager.add_module<my_module>(&manager);
}
