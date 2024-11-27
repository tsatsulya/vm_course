#ifndef VM_STACK
#define VM_STACK

#include <cstddef>
#include <cstring>
#include <vector>

template <typename T>
class Stack {
    std::vector<T> m_buffer;
    size_t m_capacity;
    size_t m_size = 0;

    void expand() {
        m_capacity *= 2;
        m_buffer.resize(m_capacity);
    }
    void squeeze() {
        m_capacity /= 2;
        m_buffer.resize(m_capacity);
    }

   public:
    Stack(const size_t capacity = 0) : m_capacity(capacity) { m_buffer.resize(m_capacity); }

    T pop() {
        if (m_size == 0) {
            return T{};
        }
        if ((--m_size) * 2 + 1 < m_capacity) {
            squeeze();
        }
        return m_buffer[m_size];
    };

    void push(T new_elem) {
        if (is_full()) {
            expand();
        }
        m_buffer.push_back(new_elem);
        m_size++;
    };

    bool is_full() { return m_size == m_capacity; }
};

#endif  // VM_STACK
