#pragma once

#include <windows.h>

namespace patcher {
    template<class T>
    void** get_vtable(T klass) {
        return *(void***)(klass);
    }

    void* patch_virtual_method(void** vtable, void* new_method, size_t methodNumber) {
        void* old_vm = vtable[methodNumber];
            
        DWORD old_protection;
        VirtualProtect(vtable, methodNumber * sizeof(void*), PAGE_EXECUTE_READWRITE, &old_protection);
        vtable[methodNumber] = new_method;
        VirtualProtect(vtable, methodNumber * sizeof(void*), old_protection, &old_protection);

        return old_vm;
    }
}
