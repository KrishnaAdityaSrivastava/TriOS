#ifndef TRIOS_MEMORY_HPP
#define TRIOS_MEMORY_HPP

#include "trit/tryte.hpp"
#include "cpu/instruction.hpp"
#include <vector>

namespace trios{
class Memory{
    static constexpr int DEFAULT_MEMORY_SIZE = 200;
    std::vector<Tryte> memory;
    public:
    Memory() : memory(DEFAULT_MEMORY_SIZE, Tryte(0)) {}
    Tryte read(const Tryte& address) const;
    Tryte write(const Tryte& address, const Tryte& value);

    EncodedInstruction readInstruction(const Tryte& address) const;
    void saveInstruction(const Tryte& address, const EncodedInstruction& instruction);

    void reset();
};
}
#endif
