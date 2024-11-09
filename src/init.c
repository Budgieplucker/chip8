#include "init.h"

#include <stdio.h>

#include "opcodes.h"

bool init_sdl(context_t* ctx, config_t* cfg) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    ctx->win = SDL_CreateWindow(
        cfg->win_title,
        cfg->win_posx, cfg->win_posy,
        cfg->win_width, cfg->win_height,
        cfg->win_flags
    );

    ctx->ren = SDL_CreateRenderer(
        ctx->win,
        cfg->ren_device,
        cfg->ren_flags
    );

    if(!ctx->win || !ctx->ren) {
        return false;
    }   

    return true;
}

void main_loop(context_t* ctx, machine_t* chip) {
    SDL_Event event;
    bool run = true;

    SDL_Rect rect = {.x = 0, .y = 0, .w = PIXEL_SCALE, .h = PIXEL_SCALE};

    while(run) {
        SDL_Delay(16);
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    run = false;
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode) {
                        case SDL_SCANCODE_Q:
                            chip->keys[0] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_W:
                            chip->keys[1] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_E:
                            chip->keys[2] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_R:
                            chip->keys[3] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_T:
                            chip->keys[4] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_Y:
                            chip->keys[5] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_U:
                            chip->keys[6] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_I:
                            chip->keys[7] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_O:
                            chip->keys[8] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_P:
                            chip->keys[9] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_A:
                            chip->keys[10] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_S:
                            chip->keys[11] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_D:
                            chip->keys[12] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_F:
                            chip->keys[13] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_G:
                            chip->keys[14] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                        case SDL_SCANCODE_H:
                            chip->keys[15] = true;
                            op_fx0a(&chip->opcode, chip);
                            break;
                    }
                    break;
            }
        }

        execute(chip);

        // TODO: basic chip8 execution loop/function call to go here
        SDL_SetRenderDrawColor(ctx->ren, 0, 0, 0, 255);
        SDL_RenderClear(ctx->ren);

        for (int i = 0; i < sizeof(chip->display); i++) {
            rect.x = ((i % 64) * PIXEL_SCALE);
            rect.y = ((i / 64) * PIXEL_SCALE);

            if(chip->display[i]) {
                
                SDL_SetRenderDrawColor(ctx->ren, 0, 255, 0, 255);
                SDL_RenderFillRect(ctx->ren, &rect);
            } 
            else {
                SDL_SetRenderDrawColor(ctx->ren, 0, 0, 0, 255);
                SDL_RenderFillRect(ctx->ren, &rect);
            }
        }

        SDL_RenderPresent(ctx->ren);
    }
}

void clean_up(context_t* ctx, config_t* cfg) {
    SDL_DestroyRenderer(ctx->ren);
    SDL_DestroyWindow(ctx->win);
    SDL_Quit();
}