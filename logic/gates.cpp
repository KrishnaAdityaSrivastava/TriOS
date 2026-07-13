#include "gates.hpp"

namespace trios {
    
Trit NotGate::evaluate(const Trit& input) const {
    if (input == POS)
        return NEG;
    else if (input == ZERO)
        return ZERO;
    return POS;
}

Trit AndGate::evaluate(const std::vector<Trit>& inputs) const {
    if (inputs.empty()) {
        return ZERO; // Return ZERO for empty input
    }

    Trit result = POS;
    for (const auto& input : inputs) {
        if (input == NEG) {
            result = (result == POS) ? NEG : POS;
        }
        else if (input == ZERO)
            return ZERO;
    }
    return result;
}

Trit OrGate::evaluate(const std::vector<Trit>& inputs) const {
    if (inputs.empty()) {
        return ZERO; // Return ZERO for empty input
    }
    Trit result = ZERO;
    for (const auto& input : inputs) {
        if ((input == POS && result == NEG) || (input == NEG && result == POS)) {
            result = ZERO;
        }
        else if (input == POS) {
            result = POS;
        }
        else if (input == NEG) {
            result = NEG;
        }
    }
    return result;
}


} // namespace trios