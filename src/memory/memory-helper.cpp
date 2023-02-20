#include "memory-helper.hpp"
#include "patcher/nop-patcher.hpp"

bytes_buffer memory_helper::nop_area(uintptr_t destination, size_t length) {
    return bytes_buffer(patcher::nop_area(destination, length));
}
