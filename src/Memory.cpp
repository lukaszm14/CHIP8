#include "Memory.hpp"
#include <fstream>

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
	}
	else
	{
		std::cout<<"Oppened ROM.\n";
	}

}
