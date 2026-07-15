#include "assembler.hpp"

namespace trios
{
    void Assembler::takeInstructionFromCli()
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
            for (char &c : opcode)
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
                this->load(parseRegister(reg), Tryte(addr));
            }
            else if (opcode == "STORE")
            {
                std::string reg;
                int addr;

                ss >> reg >> addr;
                this->store(parseRegister(reg), Tryte(addr));
            }
            else if (opcode == "MOV")
            {
                std::string dst, src;

                ss >> dst >> src;
                this->mov(parseRegister(dst), parseRegister(src));
            }
            else if (opcode == "ADD")
            {
                std::string dst, s1, s2;

                ss >> dst >> s1 >> s2;
                this->add(
                    parseRegister(dst),
                    parseRegister(s1),
                    parseRegister(s2));
            }
            else if (opcode == "SUB")
            {
                std::string dst, s1, s2;

                ss >> dst >> s1 >> s2;
                this->sub(
                    parseRegister(dst),
                    parseRegister(s1),
                    parseRegister(s2));
            }
            else if (opcode == "MUL")
            {
                std::string dst, s1, s2;

                ss >> dst >> s1 >> s2;
                this->mul(
                    parseRegister(dst),
                    parseRegister(s1),
                    parseRegister(s2));
            }
            else if (opcode == "CMP")
            {
                std::string r1, r2;

                ss >> r1 >> r2;
                this->cmp(
                    parseRegister(r1),
                    parseRegister(r2));
            }
            else if (opcode == "JMP")
            {
                int addr;
                ss >> addr;
                this->jmp(Tryte(addr));
            }
            else if (opcode == "JZ")
            {
                int addr;
                ss >> addr;
                this->jz(Tryte(addr));
            }
            else if (opcode == "CALL")
            {
                int addr;
                ss >> addr;
                this->call(Tryte(addr));
            }
            else if (opcode == "RET")
            {
                this->ret();
            }
            else if (opcode == "HALT")
            {
                this->halt();
            }
            else
            {
                std::cout << "Unknown instruction.\n";
            }
        }
    }
}