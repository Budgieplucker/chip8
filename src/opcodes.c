#include "opcodes.h"

void op_00e0(u16* opcode, machine_t* chip) {
    printf("op: 00e0\n");
    memset(chip->display, false, sizeof(*chip->display));
}

void op_00ee(u16* opcode, machine_t* chip) {
    printf("op: 00ee\n");
    chip->pc = chip->stack.arr[chip->stack.top];
    chip->sp-=1;
}

void op_1nnn(u16* opcode, machine_t* chip) {
    printf("op: 1nnn\n");
    u16 nnn = *opcode & 0x0FFF;
    chip->pc = nnn;
}   

void op_6xnn(u16* opcode, machine_t* chip) {
    printf("op: 6xnn\n");
    u16 x = (*opcode & 0x0F00) >> 8;
    u16 nn = *opcode & 0x00FF;
    chip->regs[x] = nn;
}

void op_7xnn(u16* opcode, machine_t* chip) {
    printf("op: 7xnn\n");
    u16 x = (*opcode & 0x0F00) >> 8;
    u16 nn = *opcode & 0x00FF;
    chip->regs[x] += nn;
}

void op_annn(u16* opcode, machine_t* chip) {
    printf("op: annn\n");
    u16 nnn = *opcode & 0x0FFF;
    chip->i_reg = nnn;
}

void op_dxyn(u16* opcode, machine_t* chip) {
    printf("op: dxyn\n");
    u16 x = ((*opcode & 0x0F00) >> 8);
    u16 y = ((*opcode & 0x00F0) >> 4);
    u16 n = *opcode & 0x000F;

    u16 xcoord = chip->regs[x] % 800;
    u16 ycoord = chip->regs[y] % 600;
    const u16 orig_x = xcoord;

    chip->regs[0xF] = 0;

    for(int yline = 0; yline < n; yline++) {
        u16 data = chip->ram[chip->i_reg + yline];
        xcoord = orig_x;

        for(int j = 7; j >= 0; j--) {
            bool* pixel = &chip->display[(ycoord * 64 + xcoord)];
            const bool sprite_bit = (data & (1 << j));
            
            if(sprite_bit && *pixel) {
                chip->regs[0xF] = 1;
            }

            *pixel ^= sprite_bit;

            if(++xcoord >= 64) break;
        }
        
        if(++ycoord >= 32) break;
    }
}