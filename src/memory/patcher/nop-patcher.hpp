#pragma once

#include "../buffers/runtime-buffer.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define NOP_INSTRUCTION 0x90

namespace patcher {
    runtime_buffer nop_area(uintptr_t destination, const size_t length) {
        runtime_buffer buffer;
        DWORD old_protection;

        VirtualProtect((void*)destination, length, PAGE_EXECUTE_READWRITE, &old_protection);
        {
            buffer.set_address(destination);
            buffer.reallocate_bytes((void*)destination, length);

            auto nop_area = new unsigned char[length];
            memset(nop_area, NOP_INSTRUCTION, length);

            memcpy_s((void*)destination, length, nop_area, length);

            delete[] nop_area;
        }
        VirtualProtect((void*)destination, length, old_protection, &old_protection);

        return {buffer};
    }
}
