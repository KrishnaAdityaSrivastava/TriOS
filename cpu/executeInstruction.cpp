//#include "execute.hpp"
#include "cpu.hpp"
#include <stdexcept>

namespace trios{
    void Cpu::executeInstruction(const Instruction& instruction) {
        switch (instruction.opcode) {
            case LOAD:
                // Implement LOAD logic
                setRegister(instruction.arg1, this->memory.read(instruction.arg2));
                break;
            case STORE:
                // Implement STORE logic
                this->memory.write(instruction.arg1, getRegister(instruction.arg2));
                break;
            case MOV:
                // Implement MOV logic
                setRegister(instruction.arg1, getRegister(instruction.arg2));
                break;
            case ADD:
                // Implement ADD logic
                setRegister(instruction.arg1, getRegister(instruction.arg2) + getRegister(instruction.arg3));
                break;
            case SUB:
                // Implement SUB logic
                setRegister(instruction.arg1, getRegister(instruction.arg2) - getRegister(instruction.arg3));
                break;
            case MUL:
                // Implement MUL logic
                setRegister(instruction.arg1, getRegister(instruction.arg2) * getRegister(instruction.arg3));
                break;
            case CMP:
                // Implement CMP logic
                if (getRegister(instruction.arg1) == getRegister(instruction.arg2)) {
                    registers.FLAGS.zero = true;
                } else if (getRegister(instruction.arg1).toInt() < getRegister(instruction.arg2).toInt()) {
                    registers.FLAGS.negative = true;
                    registers.FLAGS.zero = false;

                } else {
                    registers.FLAGS.zero = false;
                    registers.FLAGS.negative = false;
                }
                break;
            case JMP:
                // Implement JMP logic
                registers.PC = instruction.arg1;
                break;
            case JZ:
                // Implement JZ logic
                if (registers.FLAGS.zero) {
                    registers.PC = instruction.arg1;
                }
                break;
            case CALL:
                // Implement CALL logic
                call_stack.push(registers.PC);
                registers.PC = instruction.arg1;
                break;
            case RET:
                // Implement RET logic
                registers.PC = call_stack.top();
                call_stack.pop();
                break;
            case HALT:
                // Implement HALT logic
                throw std::runtime_error("HALT instruction executed");
                break;
            default:
                throw std::invalid_argument("Unknown opcode");
        }
    }
}