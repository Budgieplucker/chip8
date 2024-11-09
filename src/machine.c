#include "machine.h"

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "opcodes.h"

u8 font[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

// initialization
void init_chip(machine_t* chip, int argc, char* argv[]) {

    memset(chip->regs, 0, sizeof (chip->regs));
    memset(chip->ram, 0, sizeof(chip->ram));
    chip->i_reg = 0;
    chip->pc = 0;
    init_stack(&chip->stack);
    chip->sp = 0;
    chip->dt = 0;
    chip->st = 0;
    memset(&chip->display[0], false, sizeof(chip->display));
    chip->opcode = 0;

    for(int i = 0; i < sizeof(font); i++) {
        chip->ram[i] = font[i];
    }
    
    if(argc > 1) {
        load_rom(chip, argv[1]);
    } 
    else {
        fprintf(stderr, "Usage: ch8 [rom_path]");
        exit(-1);
    }
}

void load_rom(machine_t* chip, const char* path) {
    FILE* file = fopen(path, "rb");

    if(!file) {
        fprintf(stderr, "Failed to open path...\n");
        exit(-1);
    } 
    else {
        fseek(file, 0, SEEK_END);
        u32 size = ftell(file);
        rewind(file);

        // printf("ROM loaded from path: %s | Size: %d Bytes\n", path, size);
        fread(&chip->ram[0x200], 0xFFF, 1, file);
    }

    fclose(file);
}

// execution
u16 fetch_opcode(machine_t* chip) {

    u8 first = chip->ram[chip->pc];
    u8 second = chip->ram[chip->pc+1];
    
    chip->opcode = first; 
    chip->opcode <<= 8;
    chip->opcode |= second;

    chip->pc += 2;

    return chip->opcode;
}

void execute(machine_t* chip) {

    u16 opcode = fetch_opcode(chip);   

    switch(opcode & 0xF000) {
        case 0x0000:
        {
            switch(opcode & 0x00FF) {
                case 0x00E0:
                    op_00e0(&opcode, chip);
                    break;

                case 0x00EE:
                    op_00ee(&opcode, chip);
                    break;
            }
        }
        break;

        case 0x6000:
            op_6xnn(&opcode, chip);
            break;
        
        case 0x7000:
            op_7xnn(&opcode, chip);
            break;

        case 0xD000:
            op_dxyn(&opcode, chip);
            break;

        case 0x1000:
            op_1nnn(&opcode, chip);
            break;
        
        case 0xA000:
            op_annn(&opcode, chip);
            break;

        case 0x8000:
            switch(opcode & 0xF00F) {
                case 0x8000:
                    op_8xy0(&opcode, chip);
                    break;
                
                case 0x8001:
                    op_8xy1(&opcode, chip);
                    break;

                case 0x8002:
                    op_8xy2(&opcode, chip);
                    break;
                
                case 0x8003:
                    op_8xy3(&opcode, chip);
                    break;
                
                case 0x8004:
                    op_8xy4(&opcode, chip);
                    break;
                
                case 0x8005:
                    op_8xy5(&opcode, chip);
                    break;

                case 0x8006:
                    op_8xy6(&opcode, chip);
                    break;

                case 0x8007:
                    op_8xy7(&opcode, chip);
                    break;

                case 0x800E:
                    op_8xye(&opcode, chip);
                    break;
                    
            }
        break;
    }
}