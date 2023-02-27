#include "gtest/gtest.h"
#include "memory/patcher/nop-patcher.hpp"

TEST(memory_helper, nop_patcher) {
    const size_t bytes_length = 5;
    unsigned char bytes[] {
            "\x90"
            "\xA1"
            "\xD0"
            "\x8A"
    };

    unsigned char fake_bytes[] {
            "\x90"
            "\xA1"
            "\xD0"
            "\x8A"
    };

    auto copied_bytes = patcher::nop_area((uintptr_t)bytes, bytes_length);

    ASSERT_TRUE(copied_bytes.get_address() == (uintptr_t)&bytes);

    auto copied_buffer_bytes = copied_bytes.get_bytes();

    for (int i = 0; i < bytes_length; i++) {
        ASSERT_EQ((char)bytes[i], '\x90');

        ASSERT_EQ((char)fake_bytes[i], (char)copied_buffer_bytes[i]);
    }
}
