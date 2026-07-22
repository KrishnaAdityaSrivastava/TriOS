#include "assembler.hpp"

#include <fstream>
#include <sstream>
#include <cctype>
#include <unordered_map>

namespace trios
{
    void Assembler::assembleLine(const std::string &line)
    {
        std::stringstream ss(line);

        std::string opcode;
        ss >> opcode;

        if (opcode.empty())
            return;

        // Make opcode case-insensitive
        for (char &c : opcode)
        {
            c = std::toupper(
                static_cast<unsigned char>(c));
        }

        if (opcode == "LOAD")
        {
            std::string reg;
            int addr;

            ss >> reg >> addr;

            load(
                parseRegister(reg),
                Tryte(addr));
        }
        else if (opcode == "STORE")
        {
            std::string reg;
            int addr;

            ss >> reg >> addr;

            store(
                parseRegister(reg),
                Tryte(addr));
        }
        else if (opcode == "MOV")
        {
            std::string dst;
            std::string src;

            ss >> dst >> src;

            mov(
                parseRegister(dst),
                parseRegister(src));
        }
        else if (opcode == "ADD")
        {
            std::string dst;
            std::string s1;
            std::string s2;

            ss >> dst >> s1 >> s2;

            add(
                parseRegister(dst),
                parseRegister(s1),
                parseRegister(s2));
        }
        else if (opcode == "SUB")
        {
            std::string dst;
            std::string s1;
            std::string s2;

            ss >> dst >> s1 >> s2;

            sub(
                parseRegister(dst),
                parseRegister(s1),
                parseRegister(s2));
        }
        else if (opcode == "MUL")
        {
            std::string dst;
            std::string s1;
            std::string s2;

            ss >> dst >> s1 >> s2;

            mul(
                parseRegister(dst),
                parseRegister(s1),
                parseRegister(s2));
        }
        else if (opcode == "CMP")
        {
            std::string r1;
            std::string r2;

            ss >> r1 >> r2;

            cmp(
                parseRegister(r1),
                parseRegister(r2));
        }
        else if (opcode == "JMP")
        {
            int addr;

            ss >> addr;

            jmp(Tryte(addr));
        }
        else if (opcode == "JZ")
        {
            int addr;

            ss >> addr;

            jz(Tryte(addr));
        }
        else if (opcode == "CALL")
        {
            int addr;

            ss >> addr;

            call(Tryte(addr));
        }
        else if (opcode == "RET")
        {
            ret();
        }
        else if (opcode == "HALT")
        {
            halt();
        }
        else
        {
            std::cerr << "Unknown instruction: " << opcode << '\n';
        }
    }

    // void Assembler::assemble(std::istream &input)
    // {
    //     std::string line;

    //     while (std::getline(input, line))
    //     {
    //         if (line.empty())
    //             continue;

    //         assembleLine(line);
    //     }
    // }

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

            for (char &c : opcode)
            {
                c = std::toupper(
                    static_cast<unsigned char>(c));
            }

            if (opcode == "END")
                break;

            assembleLine(line);
        }
    }

    void Assembler::processInstructionFile(std::istream &file)
    {
        std::unordered_map<std::string, Tryte> labelAddresses;

        std::vector<std::string> lines;
        std::string line;

        // Read the source once so we can perform two passes
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }

        Tryte address = 0;

        for (const std::string &line : lines)
        {
            std::stringstream ss(line);

            std::string firstWord;
            ss >> firstWord;

            if (firstWord.empty())
                continue;

            if (firstWord.back() == ':')
            {
                std::string label =
                    firstWord.substr(
                        0,
                        firstWord.size() - 1);

                labelAddresses[label] = address;

                // Label-only line
                std::string instruction;
                if (!(ss >> instruction))
                    continue;

                // If the label and instruction are on the same line,
                // this still counts as one instruction.
            }

            address = address+Tryte(4);
        }

        // std::vector<std::string> rawInstructions;

        for (const std::string &line : lines)
        {
            std::stringstream ss(line);

            std::string firstWord;
            ss >> firstWord;

            if (firstWord.empty() || firstWord == ";") continue;

            // Skip label declaration
            if (firstWord.back() == ':')
            {
                // Check whether there is an instruction after the label
                if (!(ss >> firstWord)) continue;
            }
            else if (firstWord == ".MEMO"){
                //initialize memory
                
            }

            std::string rawInstruction = firstWord;
            std::string operand;

            while (ss >> operand)
            {
                auto label = labelAddresses.find(operand);

                if (label != labelAddresses.end())
                {
                    operand = std::to_string(
                        label->second.toInt());
                }

                rawInstruction += " ";
                rawInstruction += operand;
            }

            // rawInstructions.push_back(rawInstruction);
            assembleLine(rawInstruction);
        }
    }

    void Assembler::takeInstructionFromFile(const std::string &filename)
    {
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file "<< filename<< '\n';

            return;
        }
        processInstructionFile(file);
        //assemble(file);
    }
}