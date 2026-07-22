#include "memory.hpp"
#include <stdexcept>
#include <iostream>

namespace trios {
    Tryte Memory::read(const Tryte& address) const {
        int addr = address.toInt();
        if (addr < 0 || addr >= memory.size()) {
            throw std::out_of_range("Address out of range");
        }
        return memory[addr];
    }

    Tryte Memory::write(const Tryte& address, const Tryte& value) {
        int addr = address.toInt();
        //std::cout << "Writing value " << value.toInt() << " to address " << addr << std::endl;
        if (addr < 0 || addr >= memory.size()) {
            throw std::out_of_range("Address out of range" + std::to_string(memory.size()));
        }
        memory[addr] = value;
        return value;
    }

    EncodedInstruction Memory::readInstruction(const Tryte& address) const {
        int addr = address.toInt();
        if (addr < 0 || addr + 3 >= memory.size()) {
            throw std::out_of_range("Address out of range for instruction read");
        }
        EncodedInstruction instruction;
        instruction.opcode = memory[addr];
        instruction.arg1 = memory[addr + 1];
        instruction.arg2 = memory[addr + 2];
        instruction.arg3 = memory[addr + 3];
        return instruction;
    }

    void Memory::saveInstruction(const Tryte& address, const EncodedInstruction& instruction) {
        int addr = address.toInt();
        if (addr < 0 || addr + 3 >= memory.size()) {
            throw std::out_of_range("Address out of range for instruction save");
        }
        memory[addr] = instruction.opcode;
        memory[addr + 1] = instruction.arg1;
        memory[addr + 2] = instruction.arg2;
        memory[addr + 3] = instruction.arg3;
    }

    void Memory::reset(){
        memory.clear();
    }

}