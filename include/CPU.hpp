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
    void execute(Instruction& inst, Memory& memory);

    // 00EE
    void RET();

    // 1nnn
    void JP_addr(const Instruction& inst);

    // 2nnn
    void CALL_addr(const Instruction& inst);

    // 3xkk
    void SE_Vx_byte(const Instruction& inst);
    
    // 4xkk
    void SNE_Vx_byte(const Instruction& inst);
    
    // 5xy0
    void SE_Vx_Vy(const Instruction& inst);

    // 6xkk
    void LD_Vx_byte(const Instruction& inst);

    // 7xkk
    void ADD_Vx_byte(const Instruction& inst);

    // 9xy0
    void SNE_Vx_Vy(const Instruction& inst);

    // Annn
    void LD_I_addr(const Instruction& inst);
};
