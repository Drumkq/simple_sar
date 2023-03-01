#pragma once

#include <stdexcept>
#include <vector>

/***
 * @name bytes_buffer
 * @details implementation of a buffer to store bytes
 */
class bytes_buffer {
public:
    explicit bytes_buffer(void *source, size_t length);
    bytes_buffer();

    bytes_buffer(bytes_buffer &buffer);

    virtual ~bytes_buffer();

    virtual void reallocate_bytes(void *source, size_t length);

    unsigned char *const get_bytes() const;
    std::vector<unsigned char> get_std_bytes() const;

    size_t get_length() const;

    virtual void clear();

protected:
    unsigned char* m_bytes;

    size_t m_length;

    bool m_clean;
};
