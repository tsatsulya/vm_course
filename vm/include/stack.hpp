#ifndef VM_STACK
#define VM_STACK

#include <iostream>
#include <cstddef>
#include <cstring>
#include <vector>

template <typename T>
class Stack {
    std::vector<T> m_buffer;

   public:
    Stack() {}

    T pop() {
        if (m_buffer.size() == 0) {
            return T{};
        }

        auto pop_val = m_buffer.back();
        m_buffer.pop_back();

        std::cout << "Pop from stack " << pop_val << std::endl;
        dump_stack();

        return pop_val;
    };

    void push(T new_elem) {
        m_buffer.push_back(new_elem);

        std::cout << "m_buffer.size(): " << m_buffer.size() << std::endl;
        std::cout << "Push on stack " << new_elem << std::endl;
        dump_stack();
    };

    void dump_stack() {
        std::cout << "Stack: ";
        for (size_t i = 0; i != m_buffer.size(); ++i) {
            std::cout << m_buffer[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif  // VM_STACK
