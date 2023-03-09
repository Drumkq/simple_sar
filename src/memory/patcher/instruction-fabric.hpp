#pragma once

#include <cstdint>
#include <vector>

namespace patcher {
    class instruction_fabric {
    public:
        std::vector<uint8_t> create_jmp64(void* address);
    };
}
