#include <gtest/gtest.h>
#include <MyClass.hpp>

TEST(add, add) {
    EXPECT_EQ(Nitreet::MyClass::add(2, 3), 5);
}
