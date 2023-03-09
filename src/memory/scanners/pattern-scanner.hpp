#pragma once

#include <cstdlib>
#include <vector>
#include <windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

namespace scanners {
    // TODO: remove static
    static uintptr_t find_pattern(const char* module,
                           const char* pattern,
                           const char* mask) {
        static auto get_module = [](const char* module) {
            MODULEINFO m{};
            auto hmodule = GetModuleHandle(module);
            if (hmodule == nullptr) {
                return m;
            }

            GetModuleInformation(GetCurrentProcess(), hmodule, &m, sizeof(MODULEINFO));

            return m;
        };

        auto m = get_module(module);

        auto base = (uintptr_t)m.lpBaseOfDll;
        auto size = (uintptr_t)m.SizeOfImage;

        auto pattern_length = strlen(mask);

        for (DWORD i = 0; i < size - pattern_length; i++) {
            auto found = true;

            for (DWORD j = 0; j < pattern_length; j++) {
                found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
            }

            if (found) {
                return base + i;
            }
        }

        return 0x0;
    }
}
