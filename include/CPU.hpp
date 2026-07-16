#pragma once

#include <array>

#include "Memory.hpp"

struct Instruction
{
    uint8_t op = 0;
    uint16_t nnn = 0;
    uint8_t n = 0;
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t kk = 0;
};

class CPU
{
public:
    CPU();
    void reset();
    void cycle(Memory& memory);

private:
    std::array<uint8_t, 16> V;
    uint16_t I;

    std::array<uint16_t, 16> stack;

    uint16_t program_counter;
    uint8_t stack_pointer;
    
    uint8_t delay_timer;
    uint8_t sound_timer;

    uint16_t fetch(Memory& memory);
    Instruction decode(uint16_t opcode);
    void execute(Instruction inst, Memory& memory);

    void JP_addr(Instruction inst);
    void LD_Vx_byte(Instruction inst);
    void ADD_Vx_byte(Instruction inst);
};
