#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "include/graphics/graphics.h"

void set_bg(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 50, 100, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void title_txt(void) {
    SDL_DisplayMode DM;
    if (SDL_GetCurrentDisplayMode(0, &DM) == 0) {
        int hs_h = DM.h;
        int hs_w = DM.w;
    }
    else {
        printf("Home screen dimensions not found.");
    }
    
}
