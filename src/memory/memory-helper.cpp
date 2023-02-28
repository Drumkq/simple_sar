#include "memory-helper.hpp"
#include "patcher/nop-patcher.hpp"
#include "patcher/byte-patcher.hpp"

runtime_buffer memory_helper::nop_area(uintptr_t destination, size_t length) {
    return runtime_buffer(patcher::nop_area(destination, length));
}

void memory_helper::patch_area(runtime_buffer &buffer) {
    return patcher::patch_area(buffer);
}
