#pragma once

#include <array>
#include "Memory.hpp"

class CPU
{
public:
    CPU();
    void cycle(Memory& memory);
    void reset();

private:
    std::array<uint8_t, 16> V;
    uint16_t I;

    std::array<uint16_t, 16> stack;

    uint16_t program_counter;
    uint8_t stack_pointer;
    
    uint8_t delay_timer;
    uint8_t sound_timer;
};