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

    opcode = opcode << 8;
    opcode = opcode | memory.read(program_counter);
    program_counter++;

    return opcode;
}

Instruction CPU::decode(uint16_t opcode)
{
    Instruction inst;

    inst.op = (0xf000 & opcode) >> 12;
    inst.nnn = 0x0fff & opcode;
    inst.n = 0x000f & opcode;
    inst.x = (0x0f00 & opcode) >> 8;
    inst.y = (0x00f0 & opcode) >> 4;
    inst.kk = 0x00ff & opcode;

    return inst;
}

void CPU::execute(Instruction& inst, Memory& memory)
{
    switch(inst.op)
    {
        case 0x0:
            RET();
            break;
        case 0x1:
            JP_addr(inst);
            break;
        case 0x2:
            CALL_addr(inst);
            break;
        case 0x3:
            SE_Vx_byte(inst);
            break;
        case 0x4:
            SNE_Vx_byte(inst);
            break;
        case 0x5:
            SE_Vx_Vy(inst);
            break;
        case 0x6:
            LD_Vx_byte(inst);
            break;
        case 0x7:
            ADD_Vx_byte(inst);
            break;
        case 0x9:
            SNE_Vx_Vy(inst);
            break;
        case 0xA:
            LD_I_addr(inst);
            break;
        default:
            std::cout << "Not implemented\n";
            break;
    }
}

// 00EE
void CPU::RET()
{
    stack_pointer--;
    program_counter = stack[stack_pointer];
}

// 1nnn
void CPU::JP_addr(const Instruction& inst)
{
    program_counter = inst.nnn;
}

// 2nnn
void CPU::CALL_addr(const Instruction& inst)
{
    stack[stack_pointer] = program_counter;
    stack_pointer++;

    program_counter = inst.nnn;
}

// 3xkk
void CPU::SE_Vx_byte(const Instruction& inst)
{
    if(V[inst.x] == inst.kk)
        program_counter += 2;
}

// 4xkk
void CPU::SNE_Vx_byte(const Instruction& inst)
{
    if(V[inst.x] == inst.kk)
        program_counter += 2;
}

// 5xy0
void CPU::SE_Vx_Vy(const Instruction& inst)
{
    if(V[inst.x] == V[inst.y])
        program_counter += 2;
}

// 6xkk
void CPU::LD_Vx_byte(const Instruction& inst)
{
    V[inst.x] = inst.kk;
}

// 7xkk
void CPU::ADD_Vx_byte(const Instruction& inst)
{
    V[inst.x] += inst.kk;
}

// 9xy0
void CPU::SNE_Vx_Vy(const Instruction& inst)
{
    if(V[inst.x] == V[inst.y])
        program_counter += 2;
}

// Annn
void CPU::LD_I_addr(const Instruction& inst)
{
    I = inst.nnn;
}
