#include <iostream>
#include "Memory.hpp"
#include "CPU.hpp"

#include <vector>

int main()
{
	Memory memory;
	CPU cpu;

	uint16_t start = 0x200;
	std::vector<uint8_t> mess(8);
	mess = {
		0x12, 0x02, 
		0x60, 0x01,
		0x70, 0x02,
		0x73, 0x0f
	};
	for(auto c:mess)
		memory.write(start++, c);
	
	for(int i = 0; i < mess.size(); i++)
		cpu.cycle(memory);

	return 0;
}
