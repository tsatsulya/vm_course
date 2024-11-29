#ifndef VM_ARENA
#define VM_ARENA

#include <memory_resource>
#include "bytecode.h"

using arena_offset_t = size_t;
using arena_allocator_t = std::pmr::polymorphic_allocator<reg_t>;

class arena final : public std::pmr::monotonic_buffer_resource {
    void *head = nullptr;
    void *loc = nullptr;
    size_t buffer_size;

    std::pmr::monotonic_buffer_resource resource;
    arena_allocator_t allocator;

public:
    arena(size_t size) : head(new char[size]),
        resource(head, size), allocator(&resource), loc(head), buffer_size(size) {}

    ~arena() {
        resource.release();
        delete[] static_cast<reg_t *>(head);
        }

    arena(const arena &) = delete;
    arena &operator=(const arena &) = delete;

    arena(arena &&) = delete;
    arena &operator=(arena &&) = delete;

    void *do_allocate(size_t bytes, size_t alignment) override {
        void *aligned_loc = std::align(alignment, bytes, loc, buffer_size);

        if (!aligned_loc) {
            return nullptr;
        }

        loc = static_cast<reg_t *>(loc) + bytes;
        buffer_size -= bytes;

        return aligned_loc;
    }

    void do_deallocate(void * p, size_t bytes, size_t alignment) override {}

    bool do_is_equal(const memory_resource &other) const noexcept override {
        return this == &other;
    }

    std::pmr::polymorphic_allocator<reg_t> get_allocator() {
        return allocator;
    }
};

struct AllocationInfo final {
    void *ptr = nullptr;
    size_t size = 0;
};

#endif  // VM_ARENA