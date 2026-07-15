#include "cpu.hpp"
#include <stdexcept>

namespace trios{
    void Cpu::setRegister(Tryte index, const Tryte& value) {
        switch (index.toInt()) {
            case 0: registers.R0 = value; break;
            case 1: registers.R1 = value; break;
            case 2: registers.R2 = value; break;
            case 3: registers.R3 = value; break;
            case 4: registers.R4 = value; break;
            case 5: registers.R5 = value; break;
            case 6: registers.PC = value; break;
            case 7: registers.SP = value; break;
            // case 8: registers.FLAGS = value; break;
            default:
                throw std::out_of_range("Register index out of range"+std::to_string(index.toInt()));
        }
    }

    void Cpu::setRegister(Register reg, const Tryte& value) {
        int index = static_cast<int>(reg);
        if (index < 0 || index >= 8) {
            throw std::out_of_range("Register index out of range: "+std::to_string(index));
        }
        registers.GPR[index] = value;
    }

    Tryte Cpu::getRegister(Tryte index) const {
        
        switch (index.toInt()) {
            case 0: return registers.R0;
            case 1: return registers.R1;
            case 2: return registers.R2;
            case 3: return registers.R3;
            case 4: return registers.R4;
            case 5: return registers.R5;
            case 6: return registers.PC;
            case 7: return registers.SP;
            // case 8: return registers.FLAGS;
            default:
                throw std::out_of_range("Register index out of range"+std::to_string(index.toInt()));
        }
    }
    Tryte Cpu::getRegister(Register reg) const {
        int index = static_cast<int>(reg);
        if (index < 0 || index >= 8) {
            throw std::out_of_range("Register index out of range: "+std::to_string(index));
        }
        return registers.GPR[index];
    }

    void Cpu::run(Tryte startAddress) {
        registers.PC = startAddress;
        while (true) {
            // Tryte pc = registers.PC;
            EncodedInstruction encodedInstruction = memory.readInstruction(registers.PC);
            Instruction instruction = decodeInstruction(encodedInstruction);
            executeInstruction(instruction);
            if (instruction.opcode == Opcodes::HALT) break;
        }
    }



}