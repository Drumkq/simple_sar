#pragma once

#include "runtime-buffer.hpp"

class trampoline_buffer final {
public:
	trampoline_buffer();
	~trampoline_buffer();

	void reallocate(void* original, void* hook, void* trampoline_function, size_t length);
	void restore();

	void* get_original_fn() const;
	void* get_hook_fn() const;
	void* get_trampoline_fn() const;
	runtime_buffer& get_stolen_bytes();

private:
	void* m_original_function;
	void* m_hooked_function;
	void* m_trampoline_function;
	runtime_buffer m_stolen_bytes;
};
