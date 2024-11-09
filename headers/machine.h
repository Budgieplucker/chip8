#ifndef MACHINE_H
#define MACHINE_H

#include "types.h"
#include "stack.h"

typedef struct {

    u8 regs[16];
    u8 ram[0x1000];
    u16 i_reg;
    u16 pc;
    stack_t stack;
    u8 sp;
    u8 dt;
    u8 st;
    bool display[0x800];
    u16 opcode;

} machine_t;

// initialize
void init_chip(machine_t* chip, int argc, char* argv[]);

// IO
void load_rom(machine_t* chip, const char* path);

// execution
u16 fetch_opcode(machine_t* chip);
void execute(machine_t* chip);

#endif