#include "register.hpp"

namespace trios{
    Register parseRegister(const std::string& reg) {
        if (reg == "R0") return Register::R0;
        else if (reg == "R1") return Register::R1;
        else if (reg == "R2") return Register::R2;
        else if (reg == "R3") return Register::R3;
        else if (reg == "R4") return Register::R4;
        else if (reg == "R5") return Register::R5;
        else if (reg == "R6") return Register::R6;
        else if (reg == "PC") return Register::PC;
        else if (reg == "SP") return Register::SP;
        else throw std::invalid_argument("Invalid register name: " + reg);
    }
}