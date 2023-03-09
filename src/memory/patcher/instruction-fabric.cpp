#include "instruction-fabric.hpp"

#include <cstdlib>
#include <cwchar>
#include <cstdint>

namespace patcher {
    std::vector<uint8_t> instruction_fabric::create_jmp64(void* address) {
        const size_t length = 13u;
        uint8_t jump_instruction[] = { 0x49, 0xBA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, //mov 64 bit value into r10
                                          0x41, 0xFF, 0xE2 }; //jmp r10

        memcpy_s(&jump_instruction[2], sizeof(void*), &address, sizeof(void*));

        return {jump_instruction, jump_instruction + length};
    }
} // patcher