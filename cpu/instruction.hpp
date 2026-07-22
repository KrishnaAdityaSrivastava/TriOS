#ifndef TRIOS_INSTRUCTION_HPP
#define TRIOS_INSTRUCTION_HPP

#include "trit/tryte.hpp"

namespace trios{
enum class Opcodes
{
    LOAD = 0,  // LOAD DESTINATION, SOURCE      mem to reg
    STORE = 1, // STORE DESTINATION, SOURCE
    MOV = 2,   // MOV DESTINATION, SOURCE

    ADD = 10,  // ADD DESTINATION, SOURCE1, SOURCE2
    SUB = 11,  // SUB DESTINATION, SOURCE1, SOURCE2
    MUL = 12,  // MUL DESTINATION, SOURCE1, SOURCE2

    CMP = 13,  // CMP SOURCE1, SOURCE2

    JMP = 20,  // JMP ADDRESS
    JZ = 21,   // JZ ADDRESS
    CALL = 22, // CALL ADDRESS
    RET = 23,  // RET

    HALT = 26,  // HALT

    SYSCALL = 99
};

enum class priviligedInstruction{
    PRINT = 1
};

struct EncodedInstruction
{
    Tryte opcode;
    Tryte arg1;
    Tryte arg2;
    Tryte arg3;
};

struct Instruction
{
    Opcodes opcode;
    Tryte arg1;
    Tryte arg2;
    Tryte arg3;
};
}
#endif