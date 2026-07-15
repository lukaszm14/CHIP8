#include <iostream>
#include "Memory.hpp"
#include "CPU.hpp"

#include <vector>

int main()
{
	Memory memory;
	CPU cpu;

	uint16_t start = 0x200;
	std::vector<uint8_t> mess(5);
	mess = {
		0x12, 0x34, 0xbb, 0xff, 0x01
	};
	for(auto c:mess)
		memory.write(start++, c);

	cpu.cycle(memory);
	cpu.cycle(memory);
	cpu.cycle(memory);

	return 0;
}
