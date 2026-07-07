#include <iostream>
#include "Memory.hpp"

int main()
{
	Memory memory;
	memory.write(0x200, 0xAB);

	std::cout << static_cast<int>(memory.read(0x200)) << '\n';

	memory.reset();

	std::cout << static_cast<int>(memory.read(0x200)) << '\n';

	return 0;
}
