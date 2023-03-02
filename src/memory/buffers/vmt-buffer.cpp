#include "vmt-buffer.hpp"
#include "../patcher/vmt-patcher.hpp"
#include <stdexcept>

vmt_buffer::vmt_buffer(void *object)
    : m_vmtable(*(void***)object) {

}

vmt_buffer::vmt_buffer()
    : m_vmtable(nullptr) {

}

vmt_buffer::~vmt_buffer() {
    remove_methods();
}

vmt_buffer::vmt_hook vmt_buffer::update_method(void *method, size_t index) {
    auto m = m_changed_methods.emplace_back(vmt_hook{
        .index = index,
        .current_method = method,
        .old_method = patcher::patch_virtual_method(m_vmtable, method, index),
    });

    has_methods = true;

    return m;
}

void vmt_buffer::set_object(void *object) {
    if (has_methods) throw std::runtime_error("failed to update virtual method table buffer object - buffer already has updated methods");
    m_vmtable = *(void***)object;
}

void vmt_buffer::remove_methods() {
    for (auto& m : m_changed_methods) {
        patcher::patch_virtual_method(m_vmtable, m.old_method, m.index);
    }

    m_changed_methods.clear();
    m_vmtable = nullptr;
    has_methods = false;
}
