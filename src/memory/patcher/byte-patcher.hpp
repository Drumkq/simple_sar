#pragma once

#include "../buffers/runtime-buffer.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace patcher {
    void patch_area(runtime_buffer& buffer) {
        DWORD old_protection;

        uintptr_t destination = buffer.get_address();
        size_t length = buffer.get_length();

        VirtualProtect((void*)destination, length, PAGE_EXECUTE_READWRITE, &old_protection);
        {
            memcpy_s((void*)destination, length, buffer.get_bytes(), length);

            buffer.clear();
        }
        VirtualProtect((void*)destination, length, old_protection, &old_protection);
    }
}
