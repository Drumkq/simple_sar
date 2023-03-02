#include "gtest/gtest.h"

#include <modules/modules-manager.hpp>

class my_module_2 : public modules::base_module {
public:
    explicit my_module_2(modules::modules_manager* context)
            : modules::base_module(context, "my module 2"){
        a = 1000;
    }

    ~my_module_2() override = default;

    void start() override {

    }

    void update() override {
        ASSERT_EQ(a, 10);
    }

    int a = 0;
};

class my_module : public modules::base_module {
public:
    explicit my_module(modules::modules_manager* context)
            : modules::base_module(context, "my module"){

    }

    ~my_module() override = default;

    void start() override {
        auto val = m_context->get_module<my_module_2>("my module 2");
        ASSERT_TRUE(val.get() != nullptr);
        ASSERT_EQ(val->a, 1000);

        val->a = 10;
    }

    void update() override {

    }
};

TEST(modules_manager, get_module) {
    hooks::hook_manager hooks({});
    modules::modules_manager manager(hooks);

    manager.add_module<my_module>();
    manager.add_module<my_module_2>();

    manager.start();
    manager.update();
}
