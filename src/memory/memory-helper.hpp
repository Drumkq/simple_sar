#pragma once

#include "bytes-buffer.hpp"

class memory_helper {
public:
    static bytes_buffer nop_area(uintptr_t destination, size_t length);
};
