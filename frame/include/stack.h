#ifndef VM_STACK
#define VM_STACK

#include <cstddef>
#include <vector>
#include <cstring>
#include <cassert>
#include <iostream>

template<typename T>
class stack_raw {
    std::vector<T> buffer;
    size_t capacity;
    size_t size = 0;

public:

    stack_raw() : capacity(0) {}
    stack_raw(const size_t capacity_) : capacity(capacity_) {
        buffer.reserve(capacity);
    }

    T get_head() {
        if (size) {
            return buffer[size];
        }
        return T{};
    }

    T pop() {
        if (!size) return T{};
        auto elem = buffer[--size];
        buffer.erase(buffer.begin() + size);
        return elem;
    };

    void push(T new_elem) {
        // std::cout << "\nstack size/capacity : " << size << " " << capacity << '\n';
        size++;
        assert(size < capacity);
        buffer.push_back(new_elem);
    };

    void print() {
        std::cout << "stack : ";
        for (auto &i: buffer) {
            std::cout << (int)i << " ";
        }
        std::cout << '\n';
    }

    void erase() {
        buffer.resize(0);
        size = 0;
    };

    bool is_full() {
        return size == capacity;
    }

};

#endif // VM_STACK
