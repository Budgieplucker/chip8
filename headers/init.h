#ifndef INIT_H
#define INIT_H

#include "types.h"

#include <SDL2/SDL.h>

#include "machine.h"

#define PIXEL_SCALE 20

typedef struct {
    // window attributes
    char* win_title;
    u32 win_width;
    u32 win_height;
    u32 win_posx;
    u32 win_posy;
    u32 win_flags;
    // renderer attributes
    int ren_device;
    u32 ren_flags;
} config_t;

typedef struct {

    SDL_Window* win;
    SDL_Renderer* ren;

} context_t;

// initialize
bool init_sdl(context_t* ctx, config_t* cfg);

// main loop function
void main_loop(context_t* ctx, machine_t* chip);

// garbage collect
void clean_up(context_t* ctx, config_t* cfg);

#endif