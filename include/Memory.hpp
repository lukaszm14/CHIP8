#pragma once

#include <array>
#include <string>

class Memory
{
public:
    Memory();

    void reset();
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t data);
    void loadRom(const std::string& fileName);

private:
    static constexpr std::size_t MemorySize = 4096;
    static constexpr std::size_t ProgramStart = 0x200;
    std::array<uint8_t, MemorySize> memory;
};