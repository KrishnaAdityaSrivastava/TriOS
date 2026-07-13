#ifndef TRIOS_MEMORY_HPP
#define TRIOS_MEMORY_HPP

#include "trit/tryte.hpp"
#include <vector>

namespace trios{
class Memory{

    std::vector<Tryte> memory{27, Tryte(0)};// Initialize memory with 27 Trytes
    public:
    Tryte read(const Tryte& address) const;
    Tryte write(const Tryte& address, const Tryte& value);
};
}
#endif
