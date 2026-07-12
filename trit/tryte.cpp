#include "tryte.hpp"
#include <stdexcept>

namespace trios
{
    Tryte::Tryte(){

    }
    Tryte::Tryte(int value){
        if (value < -364 || value > 364) {
            throw std::out_of_range("Value must be between -364 and 364");
        }
        fromInt(value);
    }

    Trit Tryte::get(int index) const {
        if (index < 0 || index >= 6) {
            throw std::out_of_range("Index must be between 0 and 5");
        }
        return trits[index];
    }

    void Tryte::set(int index, Trit trit) {
        if (index < 0 || index >= 6) {
            throw std::out_of_range("Index must be between 0 and 5");
        }
        trits[index] = trit;
    }

    int Tryte::toInt() const {
        int value = 0;
        for (int i = 5; i >= 0; --i) {
            value = value * 3 + static_cast<int>(trits[i]);
        }
        return value;
    }

    void Tryte::fromInt(int value){
        for (int i = 0; i < 6; ++i) {
            int rem = value%3;
            
            if(rem == 2) rem = -1;
            else if (rem == -2) rem = 1;

            trits[i] = static_cast<Trit>(rem);
            value /= 3;
        }
    }

} // namespace trios
