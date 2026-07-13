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

    Tryte Tryte::operator +(const Tryte& other) const{
        Tryte result;
        int carry = 0;
        for (int i = 0;i<6;i++){
            int sum = static_cast<int>(this->get(i)) + static_cast<int>(other.get(i)) + carry;
            if (sum > 1) {
                sum -= 3;
                carry = 1;
            } else if (sum  < -1) {
                sum += 3;
                carry = -1;
            } else {
                carry = 0;
            }
            result.set(i, static_cast<Trit>(sum));
        }
        return result;
    }

    Tryte Tryte::operator -(const Tryte& other) const{
        Tryte negative_other;
        negative_other.fromInt(-other.toInt());
        return (this->operator +(negative_other));
    }

    Tryte Tryte::operator *(const Tryte& other) const{
        return Tryte(this->toInt() * other.toInt()); //later convert to bitwise if it helps in performance
    }

    bool Tryte::operator ==(const Tryte& other) const{
        return (this->toInt() == other.toInt());
    }
    bool Tryte::operator !=(const Tryte& other) const{
        return !(*this == other);
    }

} // namespace trios
