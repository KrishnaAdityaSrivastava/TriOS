//#include "execute.hpp"
#include "cpu.hpp"
#include <stdexcept>
#include <iostream>

namespace trios{
    Instruction Cpu::decodeInstruction(const EncodedInstruction& instruction) {
        Instruction decoded;
        decoded.opcode = static_cast<Opcodes>(instruction.opcode.toInt());
        decoded.arg1 = instruction.arg1;
        decoded.arg2 = instruction.arg2;
        decoded.arg3 = instruction.arg3;
        return decoded;
    }

    void Cpu::executeInstruction(const Instruction& instruction) {
        std::cout << "Executing instruction: Opcode: " << static_cast<int>(instruction.opcode)
                  << ", Arg1: " << instruction.arg1.toInt()
                  << ", Arg2: " << instruction.arg2.toInt()
                  << ", Arg3: " << instruction.arg3.toInt() << std::endl;
        switch (instruction.opcode) {
            case Opcodes::LOAD:
                // Implement LOAD logic
                setRegister(instruction.arg1, this->memory.read(instruction.arg2));
                registers.PC = registers.PC + Tryte(4);
                break;
            case Opcodes::STORE:
                // Implement STORE logic
                this->memory.write(instruction.arg1, getRegister(instruction.arg2));
                registers.PC = registers.PC + Tryte(4);
                break;
            case Opcodes::MOV:
                // Implement MOV logic
                setRegister(instruction.arg1, getRegister(instruction.arg2));
                registers.PC = registers.PC + Tryte(4);
                break;
            case Opcodes::ADD:
                // Implement ADD logic
                setRegister(instruction.arg1, getRegister(instruction.arg2) + getRegister(instruction.arg3));
                std::cout << getRegister(instruction.arg2).toInt() << " + " << getRegister(instruction.arg3).toInt() << " = " << getRegister(instruction.arg1).toInt() << std::endl;
                registers.PC = registers.PC + Tryte(4);
                break;
            case Opcodes::SUB:
                // Implement SUB logic
                setRegister(instruction.arg1, getRegister(instruction.arg2) - getRegister(instruction.arg3));
                registers.PC = registers.PC + Tryte(4);
                break;
            case Opcodes::MUL:
                // Implement MUL logic
                setRegister(instruction.arg1, getRegister(instruction.arg2) * getRegister(instruction.arg3));
                registers.PC = registers.PC + Tryte(4);
                break;
            case Opcodes::CMP:
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
                registers.PC = registers.PC + Tryte(4);
                break;
            case Opcodes::JMP:
                // Implement JMP logic
                registers.PC = instruction.arg1;
                break;
            case Opcodes::JZ:
                // Implement JZ logic
               if(registers.FLAGS.zero)
                    registers.PC = instruction.arg1;
                else
                    registers.PC = registers.PC + Tryte(4);
                break;
            case Opcodes::CALL:
                // Implement CALL logic
                call_stack.push(registers.PC+Tryte(4)); // Save return address
                registers.PC = instruction.arg1;
                break;
            case Opcodes::RET:
                // Implement RET logic
                registers.PC = call_stack.top();
                call_stack.pop();
                break;
            case Opcodes::HALT:
                // Implement HALT logic
                // throw std::runtime_error("HALT instruction executed");
                break;
            case Opcodes::SYSCALL:
                // Implement SYSCALL logic
                // int instruction = registers.R0.toInt();
                // if (instruction == 1){
                //     std::cout << 
                // }
                break;
            default:
                throw std::invalid_argument("Unknown opcode");
        }
        
    }
}