#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "include/graphics/graphics.h"
#include "include/graphics/home.h"

void launch_home(SDL_Window *window, SDL_Renderer *renderer) {
    set_bg(renderer);
    SDL_Color title_color = {
        .r = 50,
        .g = 255,
        .b = 225,
        .a = 255
    };
    TextTexture title_txt = get_txt_texture(renderer, "I-Chinese", &title_color, "./assets/Freedom-10eM.ttf", 288);
    Position title_pos = get_proportional_pos(window, 0.20, 0.10);
    render_txt(renderer, &title_txt, &title_pos);
}
