#ifndef VM_FRAME
#define VM_FRAME

#include <iostream>
#include <vector>

#include "method.hpp"
#include "stack.hpp"

class Frame {
   private:
    Method *m_func;
    uint32_t m_pc = 0;

    Stack<uint64_t> m_stack{};

    uint64_t *m_args;
    size_t m_num_args;

    Frame *m_prev;

   public:
    Frame(Method *func, size_t num_args, Frame *prev)
        : m_func(func), m_num_args(num_args), m_prev(prev) {
        m_args = new uint64_t[m_num_args];
    }
    // ~Frame() {
    //     std::cout << "Destructor\n";
    //     // delete[] m_args;
    // }

    void inc_pc(size_t instr_size) { m_pc += instr_size; }
    void set_pc(size_t pc_next) { m_pc = pc_next; }

    [[nodiscard]] auto get_pc() { return m_pc; }

    template <typename Type>
    [[nodiscard]] Type getInstr(uint32_t pc) {
        return m_func->getInstr<Type>(pc);
    }

    [[nodiscard]] auto getNumArgs() { return m_num_args; }

    void storeArg(uint64_t arg, size_t index) { m_args[index] = arg; }
    uint64_t loadArg(size_t index) { return m_args[index]; }

    [[nodiscard]] auto stack_pop() { return m_stack.pop(); }

    void stack_push(uint64_t value) { m_stack.push(value); }

    void dump_variables() {
        std::cout << "Args: ";
        for (int i = 0; i != m_num_args; ++i) {
            std::cout << m_args[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif  // VM_FRAME
