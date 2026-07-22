#include "cpu.hpp"
#include <stdexcept>
#include <string>

namespace trios{
    namespace {
        int registerIndex(Tryte index) {
            int idx = index.toInt();
            if (idx < 0 || idx >= REGISTER_COUNT) {
                throw std::out_of_range("Register index out of range: " + std::to_string(idx));
            }
            return idx;
        }

        int registerIndex(Register reg) {
            int idx = static_cast<int>(reg);
            if (idx < 0 || idx >= REGISTER_COUNT) {
                throw std::out_of_range("Register index out of range: " + std::to_string(idx));
            }
            return idx;
        }
    }

    void Cpu::setRegister(Tryte index, const Tryte& value) {
        registers.values[registerIndex(index)] = value;
    }

    void Cpu::setRegister(Register reg, const Tryte& value) {
        registers.values[registerIndex(reg)] = value;
    }

    Tryte Cpu::getRegister(Tryte index) const {
        return registers.values[registerIndex(index)];
    }

    Tryte Cpu::getRegister(Register reg) const {
        return registers.values[registerIndex(reg)];
    }

    void Cpu::run(Tryte startAddress) {
        registers.values[static_cast<int>(Register::PC)] = startAddress;
        while (true) {
            EncodedInstruction encodedInstruction = memory.readInstruction(registers.values[static_cast<int>(Register::PC)]);
            Instruction instruction = decodeInstruction(encodedInstruction);
            executeInstruction(instruction);
            if (instruction.opcode == Opcodes::HALT) break;
        }
    }
}
