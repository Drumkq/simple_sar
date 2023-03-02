#pragma once

#include <vector>

class vmt_buffer final {
public:
    struct vmt_hook {
        size_t index;
        void* current_method;
        void* old_method;
    };

public:
    explicit vmt_buffer(void* object);
    vmt_buffer();
    ~vmt_buffer();

    void set_object(void* object);
    vmt_hook update_method(void* method, size_t index);
    void remove_methods();

private:
    void** m_vmtable;
    bool has_methods = false;

    std::vector<vmt_hook> m_changed_methods;
};
