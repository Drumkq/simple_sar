#pragma once

#include <functional>

namespace utils {
    template<class R1, class R>
    class callback {
    public:
        template <class Fx, class... Types>
        void bind_callback(Fx&& method, Types&&... params) {
            m_callback = std::bind(std::forward<Fx>(method), std::forward<Types>(params)...);
        }

        template<class... Types>
        R1 call(Types... params) {
            return m_callback(params...);
        }

        bool is_bind() {
            return m_callback != nullptr;
        }

    private:
        std::function<R> m_callback;
    };
}
