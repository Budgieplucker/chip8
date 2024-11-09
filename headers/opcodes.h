#ifndef OPCODES_H
#define OPCODES_H

#include <stdio.h>
#include <memory.h>

#include "types.h"
#include "machine.h"
#include "init.h"

// ESSENTIAL
void op_00e0(u16* opcode, machine_t* chip);
void op_00ee(u16* opcode, machine_t* chip);
void op_1nnn(u16* opcode, machine_t* chip);
void op_6xnn(u16* opcode, machine_t* chip);
void op_7xnn(u16* opcode, machine_t* chip);
void op_annn(u16* opcode, machine_t* chip);
void op_dxyn(u16* opcode, machine_t* chip);

// EXTRAS
void op_2nnn(u16* opcode, machine_t* chip);
void op_3xnn(u16* opcode, machine_t* chip);
void op_4xnn(u16* opcode, machine_t* chip);
void op_5xy0(u16* opcode, machine_t* chip);
void op_8xy0(u16* opcode, machine_t* chip);
void op_8xy1(u16* opcode, machine_t* chip);
void op_8xy2(u16* opcode, machine_t* chip);
void op_8xy3(u16* opcode, machine_t* chip);
void op_8xy4(u16* opcode, machine_t* chip);
void op_8xy5(u16* opcode, machine_t* chip);
void op_8xy6(u16* opcode, machine_t* chip);
void op_8xy7(u16* opcode, machine_t* chip);
void op_8xye(u16* opcode, machine_t* chip);
void op_9xy0(u16* opcode, machine_t* chip);
void op_bnnn(u16* opcode, machine_t* chip);
void op_cxnn(u16* opcode, machine_t* chip);
void op_ex9e(u16* opcode, machine_t* chip);
void op_exa1(u16* opcode, machine_t* chip);
void op_fx07(u16* opcode, machine_t* chip);
void op_fx0a(u16* opcode, machine_t* chip);
void op_fx15(u16* opcode, machine_t* chip);
void op_fx18(u16* opcode, machine_t* chip);
void op_fx1e(u16* opcode, machine_t* chip);
void op_fx29(u16* opcode, machine_t* chip);
void op_fx33(u16* opcode, machine_t* chip);
void op_fx55(u16* opcode, machine_t* chip);
void op_fx65(u16* opcode, machine_t* chip);

#endif