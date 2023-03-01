#pragma once

#include "bytes-buffer.hpp"

class runtime_buffer : public bytes_buffer {
public:
    explicit runtime_buffer(void *source, size_t length, uintptr_t address);
    runtime_buffer();
    ~runtime_buffer();

    runtime_buffer(runtime_buffer &buffer);

    void reallocate_bytes(void *source, size_t length) override;

    void clear() override;

    void set_address(uintptr_t new_address);

    uintptr_t get_address() const;

private:
    uintptr_t m_address;
};
