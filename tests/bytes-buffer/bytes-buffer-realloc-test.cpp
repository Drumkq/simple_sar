#include "gtest/gtest.h"
#include "memory/bytes-buffer.hpp"

TEST(bytes_buffer, buffer_reallocation) {
    const size_t bytes_length = 8;
    unsigned char bytes[] {
        "\x90"
        "\xA1"
        "\xD0"
        "\x8A"
        "\x09"
        "\x13"
        "\xF1"
    };

    bytes_buffer buffer;

    buffer.reallocate_bytes(bytes, bytes_length);

    ASSERT_EQ(buffer.get_length(), bytes_length);

    auto buffer_bytes = buffer.get_bytes();
    for (int i = 0; i < bytes_length; i++) {
        ASSERT_EQ(bytes[i], buffer_bytes[i]);
    }
}
