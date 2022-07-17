#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "settings.h"
#include "world.h"

int main(int, char **) {
    World *world = new World();

    srand(time(NULL));

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Slime", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (window == NULL) {
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    SDL_Texture *texture =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                          SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    unsigned char *pixels = new unsigned char[WIDTH * HEIGHT * 4];
    for (int i = 0; i < WIDTH * HEIGHT * 4; i++) {
        pixels[i] = 0;
    }

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        world->advance();

        world->draw(pixels);

        SDL_UpdateTexture(texture, nullptr, pixels, WIDTH * 4);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_Quit();

    delete world;

    return 0;
}