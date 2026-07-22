//loads instructions into memory at the specified address

#include "assembler.hpp"

namespace trios
{
    void Assembler::load(Register reg, Tryte address)
    {
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::LOAD), Tryte((int)reg), address, Tryte(0)});
        this->address = this->address + Tryte(4);
    }

    void Assembler::store(Register reg, Tryte address)
    {
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::STORE), address, Tryte((int)reg), Tryte(0)});
        this->address = this->address + Tryte(4);
    }

    void Assembler::mov(Register reg1, Register reg2)
    {
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::MOV), Tryte((int)reg1), Tryte((int)reg2), Tryte(0)});
        this->address = this->address + Tryte(4);
    }

    void Assembler::add(Register reg1, Register reg2, Register reg3)
    {
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::ADD), Tryte((int)reg1), Tryte((int)reg2), Tryte((int)reg3)});
        this->address = this->address + Tryte(4);
    }

    void Assembler::sub(Register reg1, Register reg2, Register reg3)
    {
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::SUB), Tryte((int)reg1), Tryte((int)reg2), Tryte((int)reg3)});
        this->address = this->address + Tryte(4);
    }

    void Assembler::mul(Register reg1, Register reg2, Register reg3)
    {
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::MUL), Tryte((int)reg1), Tryte((int)reg2), Tryte((int)reg3)});
        this->address = this->address + Tryte(4);
    }

    void Assembler::cmp(Register reg1, Register reg2)
    {
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::CMP), Tryte((int)reg1), Tryte((int)reg2), Tryte(0)});
        this->address = this->address + Tryte(4);
    }

    void Assembler::jmp(Tryte address)
    {
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::JMP), address, Tryte(0), Tryte(0)});
        this->address = this->address + Tryte(4);
    }

    void Assembler::jz(Tryte address)
    {
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::JZ), address, Tryte(0), Tryte(0)});
        this->address = this->address + Tryte(4);
    }

    void Assembler::call(Tryte address)
    {
        
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::CALL), address, Tryte(0), Tryte(0)});
        this->address = this->address + Tryte(4);
    }

    void Assembler::ret()
    {
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::RET), Tryte(0), Tryte(0), Tryte(0)});
        this->address = this->address + Tryte(4);
    }

    void Assembler::halt()
    {
        memory.saveInstruction(this->address, {Tryte((int)Opcodes::HALT), Tryte(0), Tryte(0), Tryte(0)});
        this->address = this->address + Tryte(4);
    }
}
