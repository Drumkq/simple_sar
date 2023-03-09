#pragma once

#include <cstdint>
#include <stdexcept>
#include <windows.h>

#include "instruction-fabric.hpp"
#include "../buffers/trampoline-buffer.hpp"

namespace patcher {
    uintptr_t trampoline64(uintptr_t fn_hook, uintptr_t fn_original, size_t length, trampoline_buffer& bytes) {
        if (length < 13u) {
            throw std::runtime_error("trampoline deploy failed. input length less than 13 bytes");
        }

        instruction_fabric fabric;

        auto jump_to_func = fabric.create_jmp64((void*)(fn_original + length));
        auto allocated_memory = VirtualAlloc(nullptr, length, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        bytes.reallocate((void*)fn_original, (void*)fn_hook, allocated_memory, length);
        memcpy_s(allocated_memory, length, (void*)fn_original, length);
        memcpy_s((void*)((uintptr_t)allocated_memory + length), jump_to_func.size(), jump_to_func.data(), jump_to_func.size());

        auto jump_to_hook = fabric.create_jmp64((void*)fn_hook);
        
        DWORD old_protection;
        VirtualProtect((void*)fn_original, length, PAGE_EXECUTE_READWRITE, &old_protection);
        memcpy_s((void*)fn_original, jump_to_hook.size(), jump_to_hook.data(), jump_to_hook.size());
        VirtualProtect((void*)fn_original, length, old_protection, &old_protection);

        return (uintptr_t)allocated_memory;
    }
}
