#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Hooks
#include "hooks/hook-manager.hpp"
#include "hooks/hooks/speed/speed-hook.hpp"
#include "hooks/hooks/wndproc/wndproc-hook.hpp"
#include "hooks/hooks/d3d11/graphics-hook.hpp"
using namespace hooks;

// Modules
#include "modules/modules-manager.hpp"
#include "modules/features/speed-hack.hpp"
#include "modules/features/wndproc-handler.hpp"
#include "modules/features/graphics-handler.hpp"
using namespace modules;

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

    hook_manager hooks({
        std::make_shared<speed_hook>(),
        std::make_shared<wndproc_hook>(),
        std::make_shared<graphics_hook>(),
    });

    modules_manager modules(hooks);
    modules.add_module<features::speed_hack>();
    modules.add_module<features::wndproc_handler>();
    modules.add_module<features::graphics_handler>();

    auto graphics_handler = modules.get_module<features::graphics_handler>("graphics handler");

    hooks.hook_all();

    modules.start();

    while (!(GetAsyncKeyState(VK_DELETE) & 1)) {
        if (GetAsyncKeyState(VK_INSERT) & 1) {
            graphics_handler->toggle_menu();
        }

        modules.update();
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