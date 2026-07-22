#include <iostream>
#include "Memory.hpp"
#include "CPU.hpp"

#include <vector>

int main()
{
	Memory memory;
	CPU cpu;

	uint16_t start = 0x200;
	std::vector<uint8_t> program;

	memory.loadRom("tests/test.bin");
	
	for(int i = 0; i < 13; i++)
		cpu.cycle(memory);

	return 0;
}
