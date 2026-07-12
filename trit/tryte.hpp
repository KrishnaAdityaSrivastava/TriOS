#ifndef TRIOS_TRYTE_HPP
#define TRIOS_TRYTE_HPP

#include "trit.hpp"

namespace trios {

class Tryte {
private:
    Trit trits[6];

public:
    Tryte();
    Tryte(int value);
    
    Trit get(int index) const;
    void set(int index, Trit trit);
    
    int toInt() const;
    void fromInt(int value);
};

} // namespace trios

#endif