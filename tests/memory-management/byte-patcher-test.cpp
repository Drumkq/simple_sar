#include "gtest/gtest.h"
#include "memory/patcher/nop-patcher.hpp"
#include "memory/patcher/byte-patcher.hpp"

TEST(memory_helper, byte_patcher) {
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

    patcher::patch_area(copied_bytes);

    ASSERT_TRUE(copied_bytes.get_length() == 0u);
    ASSERT_TRUE(copied_bytes.get_address() == 0x0);
    ASSERT_TRUE(copied_bytes.get_bytes() == nullptr);

    for (int i = 0; i < bytes_length; i++) {
        ASSERT_TRUE(bytes[i] == fake_bytes[i]);
    }
}
