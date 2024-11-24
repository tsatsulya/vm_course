#include <cstddef>
#include <cstdint>
#include <vector>
#include <type_traits>
#include <cstring>

class stack_raw {
    std::vector<uint8_t> buffer;
    size_t capacity;
    size_t size = 0;

    void expand() {
        capacity *= 2;
        buffer.resize(capacity);
    }
    void squeeze() {
        capacity /= 2;
        buffer.resize(capacity);
    }

public:

    stack_raw() : capacity(0) {}
    stack_raw(const size_t capacity_) : capacity(capacity_) {
        buffer.resize(capacity);
    }


    uint8_t pop() {
        if (!size) return uint8_t{};
        return buffer[--size];
    };

    void push(uint8_t new_elem) {
        buffer.push_back(new_elem);
        size++;
    };

    template<typename T>
    void push(T &new_element) {
        static_assert(std::is_trivially_copyable<T>::value, "Non trivially copyable type");

        size_t elem_size = sizeof(T);
        if (size + elem_size > capacity) {
            expand();
        }

        std::memcpy(&buffer[size], &new_element, elem_size);
        size += elem_size;
    };

    template<typename T>
    T pop() {
        size_t elem_size = sizeof(T);
        if (elem_size > size) {
            return T{};
        }

        T elem = reinterpret_cast<T>(buffer.end() - elem_size, buffer.end());
        size -= elem_size;
        if ( size * 2 + 1 < capacity) {
            squeeze();
        }
        return elem;
    };

    void erase() {
        buffer.resize(0);
        size = 0;
    };

    bool is_full() {
        return size == capacity;
    }
};