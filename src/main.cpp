#include <SDL2/SDL.h>
#include "font.h"
#include "main.h"
#include <unistd.h>
#include <whb/log_cafe.h>
#include <whb/log.h>
int main(void){
    WHBLogCafeInit();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) < 0) {
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("", 0, 0, 1280, 720, SDL_WINDOW_SHOWN);
    if (!window){
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        return 1;
    }

    FontSys fsys = FontSys(renderer);
    mainloop(window, renderer, &fsys);
}

_Noreturn void mainloop(SDL_Window *window, SDL_Renderer *renderer, FontSys *font) {
    bool quit = false;
    SDL_Event ev;
    SDL_Color color;
    color.r = 255;
    color.g = 127;
    color.b = 64;
    color.a = 255;
    while (!quit) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                quit = true;
            }
        }
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        font->drawText(50, 50, "Hello World!", 24, color, 0);
        //WHBLogPrintf(font->geterr());
        // Update screen
        SDL_RenderPresent(renderer);
    }
    exit(0);
}