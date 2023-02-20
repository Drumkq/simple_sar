#include <windows.h>

#include "memory/memory-helper.hpp"

const uintptr_t assemblyModule = (uintptr_t)(GetModuleHandle("GameAssembly.dll"));

DWORD WINAPI Main(HMODULE hmodule) {
    while (!(GetAsyncKeyState(VK_INSERT) & 1)) {

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