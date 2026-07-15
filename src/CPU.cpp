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
    uint16_t opcode = memory.read(program_counter);
    program_counter++;

    opcode = opcode<<8;
    opcode = opcode | memory.read(program_counter);
    program_counter++;
}
