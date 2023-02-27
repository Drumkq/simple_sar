#include "gtest/gtest.h"
#include "memory/buffers/runtime-buffer.hpp"
#include <memory/patcher/nop-patcher.hpp>

void check_buffers(const runtime_buffer& first, const runtime_buffer& second, bool condition) {
    ASSERT_TRUE((first.get_length() == second.get_length()) == condition);
    ASSERT_TRUE((first.get_address() == second.get_address()) == condition);

    auto first_buffer_bytes = first.get_bytes();
    auto second_buffer_bytes = second.get_bytes();
    for (int i = 0; i < first.get_length(); i++) {
        ASSERT_TRUE((first_buffer_bytes[i] == second_buffer_bytes[i]) == condition);
    }
}

TEST(runtime_buffer, runtime_buffer_copy) {
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

    runtime_buffer first_buffer(bytes, bytes_length, (uintptr_t)&bytes);

    runtime_buffer second_buffer(first_buffer);

    check_buffers(first_buffer, second_buffer, true);

    first_buffer.clear();

    check_buffers(first_buffer, second_buffer, false);
}
