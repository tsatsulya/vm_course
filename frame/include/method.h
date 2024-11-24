#ifndef VM_METHOD
#define VM_METHOD

#include <cstddef>
#include <cstdint>

using offset_t = uint32_t;
using param_t = uint32_t;

class method {
    const char *name;
    offset_t offset;
    size_t params;

public:
    method(const char *name_, offset_t offset_) : name(name_), offset(offset_) {};

    size_t get_params_amount() {
        return params;
    }
};

#endif // VM_METHOD