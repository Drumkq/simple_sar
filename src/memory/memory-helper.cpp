#include "memory-helper.hpp"
#include "patcher/nop-patcher.hpp"
#include "patcher/byte-patcher.hpp"

void memory_helper::nop_area(uintptr_t destination, size_t length, runtime_buffer &in_buffer) {
    auto buffer = patcher::nop_area(destination, length);

    in_buffer.set_address(buffer.get_address());
    in_buffer.reallocate_bytes(buffer.get_bytes(), buffer.get_length());
}

void memory_helper::patch_area(runtime_buffer &buffer) {
    return patcher::patch_area(buffer);
}
