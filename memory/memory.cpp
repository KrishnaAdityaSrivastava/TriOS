#include "memory.hpp"
#include <cstddef>
#include <stdexcept>

namespace trios {
    namespace {
        std::size_t checkedAddress(const Tryte& address, std::size_t memorySize) {
            int addr = address.toInt();
            if (addr < 0 || static_cast<std::size_t>(addr) >= memorySize) {
                throw std::out_of_range("Address out of range");
            }
            return static_cast<std::size_t>(addr);
        }

        std::size_t checkedInstructionAddress(const Tryte& address, std::size_t memorySize) {
            std::size_t addr = checkedAddress(address, memorySize);
            if (addr + 3 >= memorySize) {
                throw std::out_of_range("Address out of range for instruction access");
            }
            return addr;
        }
    }

    Tryte Memory::read(const Tryte& address) const {
        return memory[checkedAddress(address, memory.size())];
    }

    Tryte Memory::write(const Tryte& address, const Tryte& value) {
        memory[checkedAddress(address, memory.size())] = value;
        return value;
    }

    EncodedInstruction Memory::readInstruction(const Tryte& address) const {
        std::size_t addr = checkedInstructionAddress(address, memory.size());
        EncodedInstruction instruction;
        instruction.opcode = memory[addr];
        instruction.arg1 = memory[addr + 1];
        instruction.arg2 = memory[addr + 2];
        instruction.arg3 = memory[addr + 3];
        return instruction;
    }

    void Memory::saveInstruction(const Tryte& address, const EncodedInstruction& instruction) {
        std::size_t addr = checkedInstructionAddress(address, memory.size());
        memory[addr] = instruction.opcode;
        memory[addr + 1] = instruction.arg1;
        memory[addr + 2] = instruction.arg2;
        memory[addr + 3] = instruction.arg3;
    }

    void Memory::reset(){
        memory.assign(DEFAULT_MEMORY_SIZE, Tryte(0));
    }

}
