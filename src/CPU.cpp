#include "CPU.hpp"

#include <iostream>

CPU::CPU()
{
    reset();
}

void CPU::reset()
{
    V.fill(0);
    I = 0;

    stack.fill(0);

    program_counter = 0x200;
    stack_pointer = 0;

    delay_timer = 0;
    sound_timer = 0;
}

void CPU::cycle(Memory& memory)
{
    uint16_t opcode = fetch(memory);
    Instruction inst = decode(opcode);
    execute(inst, memory);

}

uint16_t CPU::fetch(Memory& memory)
{
    uint16_t opcode = memory.read(program_counter);
    program_counter++;

    opcode = opcode<<8;
    opcode = opcode | memory.read(program_counter);
    program_counter++;

    return opcode;
}

Instruction CPU::decode(uint16_t opcode)
{
    Instruction inst;

    inst.op = (0xf000 & opcode) >> 12;
    inst.nnn = 0x3fff & opcode;
    inst.n = 0x000f & opcode;
    inst.x = (0x0f00 & opcode) >> 8;
    inst.y = (0x00f0 & opcode) >> 4;
    inst.kk = 0x00ff & opcode;

    return inst;
}

void CPU::execute(Instruction inst, Memory& memory)
{

}
