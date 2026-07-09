#pragma once

#include <vector>
#include <stack>

class CPU
{
public:
    CPU();

    uint16_t counter = 0;
    std::vector<uint8_t> reg;

private:
    std::stack<uint8_t> stack;

};