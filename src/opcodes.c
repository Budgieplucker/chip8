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

void op_2nnn(u16* opcode, machine_t* chip) {

    u16 nnn = *opcode & 0x0FFF;
    chip->sp++;
    push(&chip->stack, chip->pc);
    chip->pc = nnn;
}

void op_3xnn(u16* opcode, machine_t* chip) {

    u16 x = (*opcode & 0x0F00) >> 8;
    u16 nn = *opcode & 0x00FF;

    if(x == nn) {
        chip->pc+=2;
    }
}

void op_4xnn(u16* opcode, machine_t* chip) {

    u16 x = (*opcode & 0x0F00) >> 8;
    u16 nn = *opcode & 0x00FF;

    if(x != nn) {
        chip->pc+=2;
    }
}

void op_5xy0(u16* opcode, machine_t* chip) {

    u16 x = (*opcode & 0x0F00) >> 8;
    u16 Y = (*opcode & 0x00F0) >> 4;

    if(x == Y) {
        chip->pc+=2;
    }
}

void op_8xy0(u16* opcode, machine_t* chip) {

    u16 x = (*opcode & 0x0F00) >> 8;
    u16 y = (*opcode & 0x00F0) >> 4;
    chip->regs[x] = y;
}

void op_8xy1(u16* opcode, machine_t* chip) {
    
    u16 x = (*opcode & 0x0F00) >> 8;
    u16 y = (*opcode & 0x00F0) >> 4;
    chip->regs[x] |= y;
}

void op_8xy2(u16* opcode, machine_t* chip) {

    u16 x = (*opcode & 0x0F00) >> 8;
    u16 y = (*opcode & 0x00F0) >> 4;
    chip->regs[x] &= y;
}

void op_8xy3(u16* opcode, machine_t* chip) {
    u16 x = (*opcode & 0x0F00) >> 8;
    u16 y = (*opcode & 0x00F0) >> 4;
    chip->regs[x] ^= y;
}

void op_8xy4(u16* opcode, machine_t* chip) {
    u16 x = (*opcode & 0x0F00) >> 8;
    u16 y = (*opcode & 0x00F0) >> 4;
    u16 res = (x + y);

    if((res < sizeof(u8))) {
        chip->regs[0xF] = 0;
    }
    else { 
        chip->regs[0xF] = 1;
    }

    u8 store = (res & 0xFF);
    chip->regs[x] = res;
}

void op_8xy5(u16* opcode, machine_t* chip) {
    
    u8 x = *opcode & 0xFF;
    u8 y = *opcode & 0x00F0;

    if(x > y) {
        chip->regs[0xF] = 1;
    }
    else {
        chip->regs[0xF] = 0;
    }

    u8 res = (x - y);
    chip->regs[x] = res;
}

void op_8xy6(u16* opcode, machine_t* chip) {

}

void op_8xy7(u16* opcode, machine_t* chip) {

}

void op_8xye(u16* opcode, machine_t* chip) {

}

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