#include <iostream>
#include <sstream>

#include "memory/memory.hpp"
#include "trit/tryte.hpp"
#include "cpu/cpu.hpp"
#include "assembler/assembler.hpp"

using namespace trios;

int main()
{
    Memory mem;
    Cpu cpu(mem);

    std::cout << "Booting TriOS v1..." << std::endl;

    
    while (true)
    {
        std::cout << "Enter a command (assemble, run, exit): ";
        std::string command;
        std::cin >> command;

        if (command == "assem")
        {   
            int address;
            std::cin >> address;
            Assembler assembler(mem, Tryte(address));
            assembler.takeInstructionFromCli();
            std::cout << "Assembling code..." << std::endl;
        }
        else if (command == "fassem")
        {   
            std::string filename;
            std::cin >> filename;
            Assembler assembler(mem, Tryte(0));
            assembler.takeInstructionFromFile(filename);
            std::cout << "Assembling code..." << std::endl;
        }
        else if (command == "run")
        {
            // Run the CPU
            std::cout << "Running CPU..." << std::endl;
            cpu.run(Tryte(0));
        }
        else if (command == "mem")
        { // set memory
            //std::cout << "Enter address and value (e.g., 50 10): ";
            int address, value;
            std::cin >> address >> value;
            mem.write(Tryte(address), Tryte(value));
        }
        else if (command == "fetmem")
        { // fetch memory
            // std::cout << "Enter address: ";
            int address;
            std::cin >> address;
            std::cout << "Value at address " << address << ": " << mem.read(Tryte(address)).toInt() << std::endl;
        }
        else if (command == "regdump"){
            for (int i = 0;i<=6;i++){
                std::cout << "Register " <<i<<": "<< cpu.getRegister(Tryte(i)).toInt()<<std::endl;
            }
        }
        else if (command == "reset")
        {
            std::cout << "Resetting CPU..." << std::endl;
            cpu.reset();
        }
        else if (command == "exit")
        {
            std::cout << "Exiting..." << std::endl;
            break;
        }
        else
        {
            std::cout << "Unknown command. Please try again." << std::endl;
        }
    }

    return 0;
}
