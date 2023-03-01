#include "runtime-buffer.hpp"

#include <stdexcept>

runtime_buffer::runtime_buffer(void *source, size_t length, uintptr_t address)
    : bytes_buffer(source, length), m_address(address) {

}

runtime_buffer::runtime_buffer()
    : bytes_buffer(), m_address(0x0) {

}

void runtime_buffer::set_address(uintptr_t new_address) {
    m_address = new_address;
}

uintptr_t runtime_buffer::get_address() const {
    return m_address;
}

void runtime_buffer::reallocate_bytes(void *source, size_t length) {
    if (m_address == 0x0) {
        throw std::runtime_error("failed to reallocate runtime buffer - address was null. update address before buffer reallocate");
    }

    bytes_buffer::reallocate_bytes(source, length);
}

void runtime_buffer::clear() {
    if (!m_clean) {
        delete m_bytes;

        m_bytes = nullptr;

        m_length = 0;

        m_address = 0x0;

        m_clean = true;
    }
}

runtime_buffer::runtime_buffer(runtime_buffer &buffer)
    : bytes_buffer(buffer), m_address(buffer.m_address) {

}

runtime_buffer::~runtime_buffer() = default;
