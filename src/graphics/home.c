#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <stdint.h>
#include "include/graphics/graphics.h"
#include "include/graphics/home.h"

uint8_t launch_home(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_Color title_color = {
        .r = 50,
        .g = 255,
        .b = 225,
        .a = 255
    };
    SDL_Color next_text_color = {
        .r = 10,
        .g = 115,
        .b = 185,
        .a = 255
    };
    
    set_bg(renderer);

    //Title texture
    int title_size = get_proportional_font_size(renderer, 288);
    TextTexture title_txt = get_txt_texture(renderer, "I-Chinese", &title_color, "./assets/Freedom-10eM.ttf", title_size);
    Position title_pos = get_proportional_pos(renderer, &title_txt, 40, 50);

    if ((title_size < 0) || (!title_txt.texture)) {
        fprintf(stderr, "error: Failed to render title texture\n");
        return -1;
    }

    render_txt(renderer, &title_txt, &title_pos);

    //Next Text texture
    int next_text_size = get_proportional_font_size(renderer, 80);
    TextTexture next_text_txt = get_txt_texture(renderer, "Press enter to continue.", &next_text_color, "./assets/Freedom-10eM.ttf", next_text_size);
    Position next_text_pos = get_proportional_pos(renderer, &next_text_txt, 70, 50);

    if ((next_text_size < 0) || (!next_text_txt.texture)) {
        fprintf(stderr, "error: Failed to render next texture\n");
        return -1;
    }

    render_txt(renderer, &next_text_txt, &next_text_pos);

    //Cursor texture
    TextTexture cursor_text = get_png_texture(renderer, "Downloads/I_Chinese_cursor_text.png");
    if (!cursor_text.texture) {
        return -1;
    }
    //Position cursor_pos = get_proportional_pos(renderer, &cursor_text, 40, 45);
    
    return 0;

}
