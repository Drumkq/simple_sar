#pragma once

#include "buffers/runtime-buffer.hpp"

class memory_helper {
public:
    static void nop_area(uintptr_t destination, size_t length, runtime_buffer &in_buffer);
    static void patch_area(runtime_buffer& buffer);
};
