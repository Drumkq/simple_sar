#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "memory/memory-helper.hpp"

const uintptr_t assemblyModule = (uintptr_t)(GetModuleHandle("GameAssembly.dll"));

const uintptr_t speed_hack_dest_1 = assemblyModule + 0xECDF52;
const uintptr_t speed_hack_dest_2 = assemblyModule + 0xF54918;
const uintptr_t speed_hack_dest_3_test = assemblyModule + 0xF50FC4;

DWORD WINAPI Main(HMODULE hmodule) {
    bool isSpeed = false;
    bool isSpeed_test = false;

    runtime_buffer speed1;
    runtime_buffer speed2;
    runtime_buffer speed3_test;

    while (!(GetAsyncKeyState(VK_INSERT) & 1)) {
        if (GetAsyncKeyState(VK_F1) & 1) {
            isSpeed = !isSpeed;

            if (isSpeed) {
                memory_helper::nop_area(speed_hack_dest_1, 7u, speed1);
                memory_helper::nop_area(speed_hack_dest_2, 7u, speed2);
            } else {
                memory_helper::patch_area(speed1);
                memory_helper::patch_area(speed2);
            }
        }

        if (GetAsyncKeyState(VK_F2) & 1) {
            isSpeed_test = !isSpeed_test;

            if (isSpeed_test) {
                memory_helper::nop_area(speed_hack_dest_3_test, 7u, speed3_test);
            } else {
                memory_helper::patch_area(speed3_test);
            }
        }
    }

    FreeLibraryAndExitThread(hmodule, 0u);
}

BOOL WINAPI DllMain(HMODULE hmodule, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH) {
        CloseHandle(CreateThread(nullptr, 0u, (LPTHREAD_START_ROUTINE)Main, hmodule, 0u, nullptr));
    }

    return TRUE;
}