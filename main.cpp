#include <iostream>
#include "memory/memory.hpp"
#include "trit/tryte.hpp"
#include "cpu/cpu.hpp"

using namespace trios;

int main()
{
    Memory mem;
    Cpu cpu(mem);

    std::cout << "Booting TriOS v1..." << std::endl;

    // -----------------------
    // Data
    // -----------------------
    mem.write(Tryte(50), Tryte(10));
    mem.write(Tryte(51), Tryte(20));

    // -----------------------
    // Program
    // -----------------------

    // 0 : LOAD R0,[50]
    mem.saveInstruction(
        Tryte(0),
        {Tryte((int)Opcodes::LOAD), Tryte(0), Tryte(50), Tryte(0)}
    );

    // 4 : LOAD R1,[51]
    mem.saveInstruction(
        Tryte(4),
        {Tryte((int)Opcodes::LOAD), Tryte(1), Tryte(51), Tryte(0)}
    );

    // 8 : CALL 24
    mem.saveInstruction(
        Tryte(8),
        {Tryte((int)Opcodes::CALL), Tryte(24), Tryte(0), Tryte(0)}
    );

    // 12 : STORE [60],R2
    mem.saveInstruction(
        Tryte(12),
        {Tryte((int)Opcodes::STORE), Tryte(60), Tryte(2), Tryte(0)}
    );

    // 16 : JMP 36
    mem.saveInstruction(
        Tryte(16),
        {Tryte((int)Opcodes::JMP), Tryte(36), Tryte(0), Tryte(0)}
    );

    // 20 : HALT (must never execute)
    mem.saveInstruction(
        Tryte(20),
        {Tryte((int)Opcodes::HALT), Tryte(0), Tryte(0), Tryte(0)}
    );

    // -------- Function --------

    // 24 : ADD R2,R0,R1
    mem.saveInstruction(
        Tryte(24),
        {Tryte((int)Opcodes::ADD), Tryte(2), Tryte(0), Tryte(1)}
    );

    // 28 : RET
    mem.saveInstruction(
        Tryte(28),
        {Tryte((int)Opcodes::RET), Tryte(0), Tryte(0), Tryte(0)}
    );

    // 32 : HALT (must never execute)
    mem.saveInstruction(
        Tryte(32),
        {Tryte((int)Opcodes::HALT), Tryte(0), Tryte(0), Tryte(0)}
    );

    // 36 : HALT
    mem.saveInstruction(
        Tryte(36),
        {Tryte((int)Opcodes::HALT), Tryte(0), Tryte(0), Tryte(0)}
    );

    cpu.run(Tryte(0));

    std::cout << "\nExpected value at address 60 : 30\n";
    std::cout << "Actual value at address 60   : "
              << mem.read(Tryte(60)).toInt()
              << std::endl;

    return 0;
}