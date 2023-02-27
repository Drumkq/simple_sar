#include "gtest/gtest.h"
#include "memory/buffers/bytes-buffer.hpp"

TEST(bytes_buffer, buffer_clear) {
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

    bytes_buffer buffer(bytes, bytes_length);

    buffer.clear();

    ASSERT_TRUE(buffer.get_bytes() == nullptr);
}
