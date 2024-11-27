#ifndef VM_FRAME
#define VM_FRAME


#include "method.hpp"
#include "stack.hpp"

class Frame {
   private:
    Method *m_func;
    uint32_t m_pc = 0;
    Stack<uint64_t> m_stack{};

    Frame *m_prev;

   public:
    Frame(Method *func, Frame *prev) : m_func(func), m_prev(prev) {}

    void inc_pc() {
        m_pc += 1;
    }

    [[nodiscard]] uint32_t get_pc() {
        return m_pc;
    }

    [[nodiscard]] uint8_t getInstr(uint32_t pc) {
        return m_func->getInstr(pc);
    }

    [[nodiscard]] uint64_t stack_pop() {
        return m_stack.pop();
    }
    
    void stack_push(uint64_t value) {
        m_stack.push(value);
    }

};

#endif  // VM_FRAME
