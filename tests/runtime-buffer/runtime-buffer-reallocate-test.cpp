#include <gtest/gtest.h>
#include <memory/buffers/runtime-buffer.hpp>

TEST(runtime_buffer, runtime_buffer_reallocation) {
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

    runtime_buffer buffer;

    ASSERT_TRUE(buffer.get_address() == 0x0);

    buffer.set_address((uintptr_t)&bytes);
    buffer.reallocate_bytes((void*)bytes, bytes_length);

    ASSERT_TRUE(buffer.get_address() == (uintptr_t)&bytes);
}
