#include <iostream>
#include <sstream>

#include "memory/memory.hpp"
#include "trit/tryte.hpp"
#include "cpu/cpu.hpp"
#include "cpu/assembler.hpp"

using namespace trios;

Register parseRegister(const std::string& reg)
{
    if (reg == "R0") return Register::R0;
    if (reg == "R1") return Register::R1;
    if (reg == "R2") return Register::R2;
    if (reg == "R3") return Register::R3;
    if (reg == "R4") return Register::R4;
    if (reg == "R5") return Register::R5;
    if (reg == "R6") return Register::R6;
    if (reg == "PC") return Register::PC;
    if (reg == "SP") return Register::SP;

    throw std::runtime_error("Unknown register: " + reg);
}

void takeInstruction(Assembler& assembler)
{
    std::cout << "Enter instructions one per line.\n";
    std::cout << "Type END to finish assembling.\n\n";

    while (true)
    {
        std::cout << "asm> ";

        std::string line;
        std::getline(std::cin >> std::ws, line);

        if (line.empty())
            continue;

        std::stringstream ss(line);

        std::string opcode;
        ss >> opcode;

        // Make opcode case-insensitive
        for (char& c : opcode)
            c = std::toupper(static_cast<unsigned char>(c));

        if (opcode == "END")
        {
            break;
        }
        else if (opcode == "LOAD")
        {
            std::string reg;
            int addr;

            ss >> reg >> addr;
            assembler.load(parseRegister(reg), Tryte(addr));
        }
        else if (opcode == "STORE")
        {
            std::string reg;
            int addr;

            ss >> reg >> addr;
            assembler.store(parseRegister(reg), Tryte(addr));
        }
        else if (opcode == "MOV")
        {
            std::string dst, src;

            ss >> dst >> src;
            assembler.mov(parseRegister(dst), parseRegister(src));
        }
        else if (opcode == "ADD")
        {
            std::string dst, s1, s2;

            ss >> dst >> s1 >> s2;
            assembler.add(
                parseRegister(dst),
                parseRegister(s1),
                parseRegister(s2));
        }
        else if (opcode == "SUB")
        {
            std::string dst, s1, s2;

            ss >> dst >> s1 >> s2;
            assembler.sub(
                parseRegister(dst),
                parseRegister(s1),
                parseRegister(s2));
        }
        else if (opcode == "MUL")
        {
            std::string dst, s1, s2;

            ss >> dst >> s1 >> s2;
            assembler.mul(
                parseRegister(dst),
                parseRegister(s1),
                parseRegister(s2));
        }
        else if (opcode == "CMP")
        {
            std::string r1, r2;

            ss >> r1 >> r2;
            assembler.cmp(
                parseRegister(r1),
                parseRegister(r2));
        }
        else if (opcode == "JMP")
        {
            int addr;
            ss >> addr;
            assembler.jmp(Tryte(addr));
        }
        else if (opcode == "JZ")
        {
            int addr;
            ss >> addr;
            assembler.jz(Tryte(addr));
        }
        else if (opcode == "CALL")
        {
            int addr;
            ss >> addr;
            assembler.call(Tryte(addr));
        }
        else if (opcode == "RET")
        {
            assembler.ret();
        }
        else if (opcode == "HALT")
        {
            assembler.halt();
        }
        else
        {
            std::cout << "Unknown instruction.\n";
        }
    }
}

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

        if (command == "assemble")
        {   
            int address;
            std::cin >> address;
            Assembler assembler(mem, Tryte(address));
            takeInstruction(assembler);
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
