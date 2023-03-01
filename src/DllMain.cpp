#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "hooks/hook-manager.hpp"

// Hooks
#include "hooks/hooks/speed/speed-hook.hpp"
using namespace hooks;

#include <spdlog/spdlog.h>

#pragma region console_utils
FILE* allocate_console() {
#ifdef _DEBUG
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    return f;
#endif

    return nullptr;
}

void free_console(FILE* f) {
#ifdef _DEBUG
    FreeConsole();

    fclose(f);
#endif
}
#pragma endregion

DWORD WINAPI Main(HMODULE hmodule) {
    auto console_handle = allocate_console();

#ifdef _DEBUG
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::info);
#endif

    auto hk_speed_hook = std::make_shared<speed_hook>();

    hook_manager hooks({
        hk_speed_hook,
    });

    hooks.hook_all();

    while (!(GetAsyncKeyState(VK_INSERT) & 1)) {
        if (GetAsyncKeyState(VK_F1) & 1) {
            hk_speed_hook->toggle();
        }
    }

    hooks.unhook_all();

    free_console(console_handle);

    FreeLibraryAndExitThread(hmodule, 0u);
}

BOOL WINAPI DllMain(HMODULE hmodule, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH) {
        CloseHandle(CreateThread(nullptr, 0u, (LPTHREAD_START_ROUTINE)Main, hmodule, 0u, nullptr));
    }

    return TRUE;
}