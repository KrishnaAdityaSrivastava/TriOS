#include <cassert>
#include <sstream>

#include "assembler/assembler.hpp"
#include "cpu/cpu.hpp"
#include "memory/memory.hpp"
#include "trit/tryte.hpp"

using namespace trios;

void test_tryte_defaults_and_arithmetic() {
    Tryte zero;
    assert(zero.toInt() == 0);
    assert((Tryte(5) + Tryte(-2)).toInt() == 3);
    assert((Tryte(5) - Tryte(7)).toInt() == -2);
    assert((Tryte(-3) * Tryte(4)).toInt() == -12);

    Tryte value(-1);
    ++value;
    assert(value.toInt() == 0);
    ++value;
    assert(value.toInt() == 1);
    ++value;
    assert(value.toInt() == 2);
}

void test_memory_reset_restores_addressable_zeroed_memory() {
    Memory memory;
    memory.write(Tryte(10), Tryte(42));
    assert(memory.read(Tryte(10)).toInt() == 42);

    memory.reset();

    assert(memory.read(Tryte(10)).toInt() == 0);
    memory.write(Tryte(199), Tryte(-7));
    assert(memory.read(Tryte(199)).toInt() == -7);
}

void test_cpu_register_mapping_has_no_duplicate_state() {
    Memory memory;
    Cpu cpu(memory);

    cpu.setRegister(Register::R6, Tryte(33));
    assert(cpu.getRegister(Tryte(6)).toInt() == 33);

    cpu.setRegister(Tryte(7), Tryte(44));
    assert(cpu.getRegister(Register::PC).toInt() == 44);

    cpu.setRegister(Tryte(8), Tryte(55));
    assert(cpu.getRegister(Register::SP).toInt() == 55);
}

void test_cpu_can_load_into_r6_without_corrupting_pc() {
    Memory memory;
    memory.write(Tryte(50), Tryte(17));

    Assembler assembler(memory, Tryte(0));
    assembler.load(Register::R6, Tryte(50));
    assembler.halt();

    Cpu cpu(memory);
    cpu.run(Tryte(0));

    assert(cpu.getRegister(Register::R6).toInt() == 17);
    assert(cpu.getRegister(Register::PC).toInt() == 4);
}

void test_assembler_file_processing_ignores_comments_and_resolves_labels() {
    Memory memory;
    Assembler assembler(memory, Tryte(0));

    std::istringstream source(R"tri(
        ; comment-only line should not consume instruction space
        LOAD R0 100 ; inline comments should be ignored
    loop:
        ADD R1 R0 R0
        JZ end
        JMP loop
    end:
        HALT
    )tri");

    assembler.processInstructionFile(source);

    assert(memory.readInstruction(Tryte(0)).opcode.toInt() == static_cast<int>(Opcodes::LOAD));
    assert(memory.readInstruction(Tryte(4)).opcode.toInt() == static_cast<int>(Opcodes::ADD));

    EncodedInstruction jz = memory.readInstruction(Tryte(8));
    assert(jz.opcode.toInt() == static_cast<int>(Opcodes::JZ));
    assert(jz.arg1.toInt() == 16);

    EncodedInstruction jmp = memory.readInstruction(Tryte(12));
    assert(jmp.opcode.toInt() == static_cast<int>(Opcodes::JMP));
    assert(jmp.arg1.toInt() == 4);

    assert(memory.readInstruction(Tryte(16)).opcode.toInt() == static_cast<int>(Opcodes::HALT));
}

int main() {
    test_tryte_defaults_and_arithmetic();
    test_memory_reset_restores_addressable_zeroed_memory();
    test_cpu_register_mapping_has_no_duplicate_state();
    test_cpu_can_load_into_r6_without_corrupting_pc();
    test_assembler_file_processing_ignores_comments_and_resolves_labels();

    return 0;
}
