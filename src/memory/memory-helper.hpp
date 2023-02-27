#pragma once

#include "buffers/bytes-buffer.hpp"
#include "buffers/runtime-buffer.hpp"

class memory_helper {
public:
    static runtime_buffer nop_area(uintptr_t destination, size_t length);
};
