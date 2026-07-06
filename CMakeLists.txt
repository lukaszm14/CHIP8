cmake_minimum_required(VERSION 3.16)

project(CHIP8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(chip8 
    src/main.cpp 
    src/Memory.cpp
)

target_include_directories(chip8 PRIVATE include)
