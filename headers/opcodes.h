#ifndef OPCODES_H
#define OPCODES_H

#include <stdio.h>
#include <memory.h>

#include "types.h"
#include "machine.h"
#include "init.h"

void op_00e0(u16* opcode, machine_t* chip);
void op_00ee(u16* opcode, machine_t* chip);
void op_1nnn(u16* opcode, machine_t* chip);
void op_6xnn(u16* opcode, machine_t* chip);
void op_7xnn(u16* opcode, machine_t* chip);
void op_annn(u16* opcode, machine_t* chip);
void op_dxyn(u16* opcode, machine_t* chip);

#endif