#ifndef TRIOS_REGISTER_HPP
#define TRIOS_REGISTER_HPP

#include <array>
#include <string>
#include <stdexcept>
#include "trit/tryte.hpp"

namespace trios{
struct FlagsRegister{
    bool zero;
    bool carry;
    bool negative;
    bool overflow;
};
struct CpuRegister{
    std::array<Tryte, 7> GPR;  // General Purpose Registers R0-R5
    Tryte R0;
    Tryte R1;
    Tryte R2;
    Tryte R3;
    Tryte R4;
    Tryte R5;
    Tryte R6;
    Tryte PC;
    Tryte SP;
    FlagsRegister FLAGS;
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