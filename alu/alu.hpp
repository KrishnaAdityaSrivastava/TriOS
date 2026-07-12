#include "tryte.hpp"

namespace trios{
class ALU{

    Tryte operator+(const Tryte& other) const;
    Tryte operator-(const Tryte& other) const;
    Tryte operator*(const Tryte& other) const;
    
    bool operator==(const Tryte& other) const;
    bool operator!=(const Tryte& other) const;
    
};

}
