#include "Memory.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

Memory::Memory()
{
    reset();
}

void Memory::reset()
{
	memory.fill(0);
}

uint8_t Memory::read(uint16_t address)
{
	return memory.at(address);
}

void Memory::write(uint16_t address, uint8_t data)
{
	memory.at(address) = data;
}
    
void Memory::loadRom(const std::string& fileName)
{
	//file openning
	std::ifstream file(fileName, std::ios::binary);

	if(!file.is_open())
	{
		std::cout<<"Cannot open ROM.\n";
		return;
	}
	else
	{
		//opened file size checking
		file.seekg(0, std::ios_base::end);
		auto fileSize = file.tellg();
		file.seekg(0, std::ios_base::beg);

		if(fileSize > MemorySize - ProgramStart)
		{
			std::cout<<"File too big.\n";
			return;
		}

		//memory
		std::vector<uint8_t> buffer(fileSize);
		file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
		
		std::copy(buffer.begin(), buffer.end(), memory.begin() + ProgramStart);
	}
}
