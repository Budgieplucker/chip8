#include "init.h"
#include "machine.h"

int main(int argc, char* argv[]) {

    // initialize sdl2 library and set the context attributes
    config_t cfg = {
        // win
        "ch8-emu",
        1200, 600,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE,
        // ren
        -1,
        SDL_RENDERER_ACCELERATED
    };

    // initialize core objects
    context_t ctx = {0};
    machine_t chip = {0};
    init_chip(&chip, argc, argv);
    init_sdl(&ctx, &cfg);

    // TODO: main execution loop and chip8-machine initialization
    main_loop(&ctx, &chip);

    // cleans up after memory allocations (USED AT THE END OF THE PROGRAM)
    clean_up(&ctx, &cfg);

    return 0;
}