#ifndef TRIOS_REGISTER_HPP
#define TRIOS_REGISTER_HPP

#include <array>
#include <string>
#include <stdexcept>
#include "trit/tryte.hpp"

namespace trios{
constexpr int GENERAL_REGISTER_COUNT = 7;
constexpr int REGISTER_COUNT = 9;

struct FlagsRegister{
    bool zero = false;
    bool carry = false;
    bool negative = false;
    bool overflow = false;
};

struct CpuRegister{
    std::array<Tryte, REGISTER_COUNT> values{};
    FlagsRegister FLAGS{};
};

enum class Register : int
{
    R0 = 0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    PC,
    SP
};

Register parseRegister(const std::string& reg);

}
#endif
