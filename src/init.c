#include "init.h"

#include <stdio.h>

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