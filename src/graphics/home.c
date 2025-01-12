#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "include/graphics/graphics.h"
#include "include/graphics/home.h"

void launch_home(SDL_Renderer *renderer) {
    set_bg(renderer);
    SDL_Color title_color = {
        .r = 230,
        .g =255,
        .b = 245,
        .a = 255
    };
    TextTexture title_txt = get_txt_texture(renderer, "I_Chinese", &title_color, "./assets/Freedom-10eM.ttf", 16);
    Position title_pos = get_proportional_pos(0.33, 0.25);
    render_txt(renderer, &title_txt, &title_pos);
}