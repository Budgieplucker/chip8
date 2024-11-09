cmake_minimum_required(VERSION 3.25)

project(ch8)

include_directories(headers)

add_executable(ch8
    src/main.c
    headers/init.h
    src/init.c
    headers/opcodes.h
    src/opcodes.c
    headers/machine.h
    src/machine.c
    headers/types.h
    headers/stack.h
    src/stack.c)

find_package(SDL2 REQUIRED)
target_link_libraries(ch8 PUBLIC SDL2main SDL2)