#ifndef TRIOS_ASSEMBLER_HPP
#define TRIOS_ASSEMBLER_HPP

#include "memory/memory.hpp"
#include "cpu/register.hpp"
    #include <iostream>
    #include <sstream>


namespace trios{
class Assembler {
    Memory &memory;
    Tryte address; // Current address for instruction placement

public:
    Assembler(Memory &memory,Tryte address) : memory(memory), address(address) {};

    void takeInstructionFromCli();

    void load(Register reg, Tryte address);
    void store(Register reg, Tryte address);
    void mov(Register reg1, Register reg2);
    void add(Register reg1, Register reg2, Register reg3);
    void sub(Register reg1, Register reg2, Register reg3);
    void mul(Register reg1, Register reg2, Register reg3);
    void cmp(Register reg1, Register reg2);
    void jmp(Tryte address);
    void jz(Tryte address);
    void call(Tryte address);
    void ret();
    void halt();
};
}

#endif