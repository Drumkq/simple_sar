#include "bytes-buffer.hpp"

bytes_buffer::bytes_buffer(void *source, size_t length)
    : m_length(length), m_clean(false), m_bytes(nullptr) {
    m_bytes = new unsigned char[m_length];

    memcpy_s((void*)m_bytes, m_length, source, length);
}

bytes_buffer::bytes_buffer(bytes_buffer &buffer)
        : m_length(buffer.m_length), m_clean(false) {
    m_bytes = new unsigned char[m_length];

    memcpy_s(m_bytes, m_length, buffer.m_bytes, buffer.m_length);
}

bytes_buffer::bytes_buffer()
        : m_bytes(nullptr), m_length(0u), m_clean(true) {

}

bytes_buffer::~bytes_buffer() {
    delete m_bytes;
}

void bytes_buffer::reallocate_bytes(void *source, size_t length) {
    clear();

    m_length = length;

    m_bytes = new unsigned char[m_length];

    memcpy_s(m_bytes, m_length, source, length);

    m_clean = false;
}

unsigned char *const bytes_buffer::get_bytes() const {
    return m_bytes;
}

void bytes_buffer::clear() {
    if (!m_clean) {
        delete m_bytes;

        m_bytes = nullptr;

        m_length = 0;

        m_clean = true;
    }
}

size_t bytes_buffer::get_length() const {
    return m_length;
}

std::vector<unsigned char> bytes_buffer::get_std_bytes() const {
    auto v = std::vector<unsigned char>();

    for (int i = 0; i < m_length; i++) {
        v.push_back(m_bytes[i]);
    }

    return v;
}
