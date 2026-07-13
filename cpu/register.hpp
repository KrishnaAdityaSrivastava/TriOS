#ifndef TRIOS_REGISTER_HPP
#define TRIOS_REGISTER_HPP

#include "trit/tryte.hpp"

namespace trios{
struct FlagsRegister{
    bool zero;
    bool carry;
    bool negative;
    bool overflow;
};
struct CpuRegister{
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
}
#endif