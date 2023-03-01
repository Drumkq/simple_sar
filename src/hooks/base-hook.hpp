#pragma once

namespace hooks {
    class base_hook {
    public:
        base_hook(const char* name, bool optional = false)
            : name(name), optional(optional) {

        }
        virtual ~base_hook() = default;

        virtual void hook() = 0;
        virtual void unhook() = 0;

        bool is_hooked() const {
            return m_hooked;
        }

        void toggle() {
            !m_hooked ? hook() : unhook();
        }

        const bool optional;

        const char* const name;

    protected:
        bool m_hooked = false;
    };
}
