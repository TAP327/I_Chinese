#include <SDL.h>
#include <SDL_timer.h>
#include "include/graphics/home.h"

void set_bg(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 50, 100, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
