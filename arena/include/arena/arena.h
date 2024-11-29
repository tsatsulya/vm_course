#ifndef VM_ARENA
#define VM_ARENA

#include <memory_resource>
#include "bytecode.h"
#include <new>
#include <cassert>
#include <memory_resource>

class FixedBufferResource : public std::pmr::memory_resource {
public:
    explicit FixedBufferResource(std::size_t size)
        : buffer_(new reg_t[size]), size_(size), offset_(0) {}

    ~FixedBufferResource() override {
        delete[] buffer_;
    }

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        std::size_t aligned_offset = align_offset(offset_, alignment);

        if (aligned_offset + bytes > size_) {
            throw std::bad_alloc();
        }

        void* ptr = buffer_ + aligned_offset;
        offset_ = aligned_offset + bytes;
        return ptr;
    }

    void do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) override {
        // In a fixed buffer resource, we do not deallocate individual blocks.
        // This is a no-op.
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

private:
    reg_t* buffer_;         // Buffer for allocations
    std::size_t size_;     // Total size of the buffer
    std::size_t offset_;   // Current offset for allocations

    // Helper function to align the offset
    std::size_t align_offset(std::size_t offset, std::size_t alignment) const {
        if (alignment == 0) return offset; // No alignment needed
        std::size_t misalignment = offset % alignment;
        return misalignment == 0 ? offset : offset + (alignment - misalignment);
    }
};

#endif // VM_ARENA