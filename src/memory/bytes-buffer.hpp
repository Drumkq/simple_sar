#pragma once

#include <stdexcept>

class bytes_buffer {
public:
    explicit bytes_buffer(void *source, size_t length);
    bytes_buffer();

    bytes_buffer(bytes_buffer& buffer);

    ~bytes_buffer();

    void reallocate_bytes(void *source, size_t length);

    unsigned char const* const get_bytes() const;

    size_t get_length() const;

    void clear();

private:
    unsigned char* m_bytes;

    size_t m_length;

    bool m_clean;
};