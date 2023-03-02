#pragma once

namespace modules {
    class base_module {
    public:
        base_module(struct modules_manager* context, const char* name)
            : m_context(context), name(name) {

        }
        virtual ~base_module() = default;

        virtual void start() = 0;
        virtual void update() = 0;

        const char* const name;

    protected:
        struct modules_manager* const m_context;
    };
}
