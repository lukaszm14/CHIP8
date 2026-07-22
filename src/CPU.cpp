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

void CPU::execute(const Instruction& inst, Memory& memory)
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
        case 0x8:
            execute_alu(inst);
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

void CPU::execute_alu(const Instruction& inst)
{
    switch (inst.n)
    {
    case 0x0:
        LD_Vx_Vy(inst);
        break;
    case 0x1:
        OR_Vx_Vy(inst);
        break;
    case 0x2:
        AND_Vx_Vy(inst);
        break;
    case 0x3:
        XOR_Vx_Vy(inst);
        break;
    case 0x4:
        ADD_Vx_Vy(inst);
        break;
    case 0x5:
        SUB_Vx_Vy(inst);
        break;
    case 0x6:
        SHR_Vx_Vy(inst);
        break;
    case 0x7:
        SUBN_Vx_Vy(inst);
        break;
    case 0xE:
        SHL_Vx_Vy(inst);
        break;
    default:
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
    if(V[inst.x] != inst.kk)
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

// 8xy0
void CPU::LD_Vx_Vy(const Instruction& inst)
{
    V[inst.x] = V[inst.y];
}

// 8xy1
void CPU::OR_Vx_Vy(const Instruction& inst)
{
    V[inst.x] = V[inst.x] | V[inst.y];
}

// 8xy2
void CPU::AND_Vx_Vy(const Instruction& inst)
{
    V[inst.x] = V[inst.x] & V[inst.y];
}

// 8xy3
void CPU::XOR_Vx_Vy(const Instruction& inst)
{
    V[inst.x] = V[inst.x] ^ V[inst.y];
}

// 8xy4
void CPU::ADD_Vx_Vy(const Instruction& inst)
{
    uint16_t sum = V[inst.x] + V[inst.y];
    if(sum > 0xFF)
        V[0xF] = 1;
    else
        V[0xF] = 0;
    V[inst.x] = static_cast<uint8_t>(sum);
}

// 8xy5
void CPU::SUB_Vx_Vy(const Instruction& inst)
{
    if(V[inst.x] > V[inst.y])
        V[0xF] = 1;
    else
        V[0xF] = 0;

    V[inst.x] = V[inst.x] - V[inst.y];

}

// 8xy6
void CPU::SHR_Vx_Vy(const Instruction& inst)
{
    V[0xF] = V[inst.x] & 0x01;
    V[inst.x] = V[inst.x] >> 2;
}

// 8xy7
void CPU::SUBN_Vx_Vy(const Instruction& inst)
{
    if(V[inst.y] > V[inst.x])
        V[0xF] = 1;
    else
        V[0xF] = 0;

    V[inst.x] = V[inst.y] - V[inst.x];
}

// 8xyE
void CPU::SHL_Vx_Vy(const Instruction& inst)
{
    V[0xF] = (V[inst.x] & 0x80) >> 7;
    V[inst.x] = V[inst.x] << 1;
}

// 9xy0
void CPU::SNE_Vx_Vy(const Instruction& inst)
{
    if(V[inst.x] != V[inst.y])
        program_counter += 2;
}

// Annn
void CPU::LD_I_addr(const Instruction& inst)
{
    I = inst.nnn;
}
