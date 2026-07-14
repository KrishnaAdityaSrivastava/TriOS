#ifndef TRIOS_MEMORY_HPP
#define TRIOS_MEMORY_HPP

#include "trit/tryte.hpp"
#include "cpu/instruction.hpp"
#include <vector>

namespace trios{
class Memory{

    std::vector<Tryte> memory;
    public:
    Memory() : memory(100, Tryte(0)) {} // Initialize memory with 100 Trytes
    Tryte read(const Tryte& address) const;
    Tryte write(const Tryte& address, const Tryte& value);

    EncodedInstruction readInstruction(const Tryte& address) const;
    void saveInstruction(const Tryte& address, const EncodedInstruction& instruction);
};
}
#endif
