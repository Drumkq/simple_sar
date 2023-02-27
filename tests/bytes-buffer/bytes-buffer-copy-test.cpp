#include "gtest/gtest.h"
#include "memory/buffers/bytes-buffer.hpp"
#include <memory/patcher/nop-patcher.hpp>

void check_buffers(const bytes_buffer& first, const bytes_buffer& second, bool condition) {
    ASSERT_TRUE((first.get_length() == second.get_length()) == condition);

    auto first_buffer_bytes = first.get_bytes();
    auto second_buffer_bytes = second.get_bytes();
    for (int i = 0; i < first.get_length(); i++) {
        ASSERT_TRUE((first_buffer_bytes[i] == second_buffer_bytes[i]) == condition);
    }
}

TEST(bytes_buffer, buffer_copy) {
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

    bytes_buffer first_buffer(bytes, bytes_length);

    bytes_buffer second_buffer(first_buffer);

    check_buffers(first_buffer, second_buffer, true);

    first_buffer.clear();

    check_buffers(first_buffer, second_buffer, false);
}
