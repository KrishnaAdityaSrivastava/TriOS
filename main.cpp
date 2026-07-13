#include <iostream>
#include "memory/memory.hpp"
#include "trit/tryte.hpp"
#include "cpu/cpu.hpp"

using namespace trios;
int main(){
    std::cout <<"Test";
    Memory mem;
    Cpu cpu(mem);

    // Tryte address(5);
    // Tryte value(10);

    // mem.write(address, value);
    // Tryte readValue = mem.read(address);
    
    Tryte testValue(10);
    Tryte testAddress(5);
    std::cout << "Value at address " << testAddress.toInt() << ": " << testValue.toInt() << std::endl;
    

    return 0;
}