#include "trampoline-buffer.hpp"
#include <Windows.h>

trampoline_buffer::trampoline_buffer()
	: m_original_function(nullptr), 
	m_hooked_function(nullptr), 
	m_trampoline_function(nullptr) {
}

trampoline_buffer::~trampoline_buffer() = default;

void trampoline_buffer::reallocate(void* original, void* hook, void* trampoline_function, size_t length) {
	m_original_function = original;
	m_hooked_function = hook;
	m_trampoline_function = trampoline_function;
	m_stolen_bytes.set_address((uintptr_t)original);
	m_stolen_bytes.reallocate_bytes(original, length);
}

void trampoline_buffer::restore() {
	DWORD old_prot;
	size_t length = m_stolen_bytes.get_length();
	VirtualFree(m_trampoline_function, NULL, MEM_RELEASE);
	VirtualProtect((void*)m_original_function, length, PAGE_EXECUTE_READWRITE, &old_prot);
	memcpy_s((void*)m_original_function, length, m_stolen_bytes.get_bytes(), length);
	VirtualProtect((void*)m_original_function, length, old_prot, &old_prot);
}

void* trampoline_buffer::get_original_fn() const {
	return m_original_function;
}

void* trampoline_buffer::get_hook_fn() const {
	return m_hooked_function;
}

void* trampoline_buffer::get_trampoline_fn() const {
	return m_trampoline_function;
}

runtime_buffer& trampoline_buffer::get_stolen_bytes() {
	return m_stolen_bytes;
}
