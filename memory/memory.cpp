#include "memory.hpp"
#include <stdexcept>

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
        if (addr < 0 || addr >= memory.size()) {
            throw std::out_of_range("Address out of range" + std::to_string(memory.size()));
        }
        memory[addr] = value;
        return value;
    }
}