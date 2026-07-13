#ifndef TRIOS_CPU_HPP
#define TRIOS_CPU_HPP

#include <stack>

#include "trit/tryte.hpp"
#include "cpu/register.hpp"
#include "cpu/instruction.hpp"
#include "memory/memory.hpp"

namespace trios {
    class Cpu {
        trios::CpuRegister registers;
        Memory& memory;
        std::stack<Tryte> call_stack;
    public:
        Cpu(Memory& memory) : registers(), memory(memory) {};

        void executeInstruction(const Instruction& instruction);
        void setRegister(Tryte index, const Tryte& value);
        Tryte getRegister(Tryte index) const;

    };
}
#endif