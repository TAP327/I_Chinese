#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "include/graphics/graphics.h"
#include <SDL_rwops.h>


void set_bg(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 60, 215);
    SDL_RenderClear(renderer);
}

int get_proportional_font_size(SDL_Window *window, SDL_Renderer *renderer, const int size) {
    SDL_DisplayMode DM;
    int dm_h, dm_w = 0;
    int hs_h, hs_w = 0;
    int proportional_size = 0;
    
    if ((SDL_GetCurrentDisplayMode(0, &DM) == 0)) {
        dm_h = DM.h;
        dm_w = DM.w;
    }
    else {
        fprintf(stderr, "error: Display mode dimensions not found. (%s)\n", SDL_GetError());
        return -1;
    }
    if ((SDL_GetRendererOutputSize(renderer, &hs_w, &hs_h) == 0)) {
        if (hs_w <= hs_h) {
            proportional_size = ((size*hs_w)/dm_w);
        }
        else {
            proportional_size = ((size*hs_h)/dm_h);
        }
        return proportional_size;
    }
    else {
        fprintf(stderr, "error: Home screen dimensions not found. (%s)\n", SDL_GetError());
        return -2;
    }
}

TextTexture get_txt_texture(SDL_Renderer *renderer, const char *text, SDL_Color *color, const char *file, const int size) {
    TTF_Font *font = TTF_OpenFont(file, size);

    TextTexture txt_texture = {
        NULL,
        0,
        0
    };

    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, *color);
    if (!surface) {
        fprintf(stderr, "Failed to render text surface: %s\n", TTF_GetError());
        return txt_texture;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    txt_texture.texture = texture;
    if (!txt_texture.texture) {
        fprintf(stderr, "Failed to create texture from surface: %s\n", SDL_GetError());
        return txt_texture;
    }

    txt_texture.height = surface->h;
    txt_texture.width = surface->w;

    return txt_texture;
}

Position get_proportional_pos(SDL_Renderer *renderer, const TextTexture *texture, float down_shift, const float right_shift) {
    Position pos = {
        0,
        0
    };

    int hs_h, hs_w = 0;
    if ((SDL_GetRendererOutputSize(renderer, &hs_w, &hs_h) == 0 )) {
       pos.x = ((right_shift*hs_w)/100)-(texture->width/2);
       pos.y = ((down_shift*hs_h)/100)-(texture->height/2);
    }
    else {
        fprintf(stderr, "error: Home screen dimensions not found. (%s)\n", SDL_GetError());
    }


    return pos;
}

void render_txt(SDL_Renderer *renderer, TextTexture *texture, Position *pos) {
    if (!renderer || !texture || !texture->texture || !pos) {
        fprintf(stderr, "Invalid parameters passed to render_txt.\n");
        return;
    }
    SDL_Rect dest_rect = {
        .x = pos->x, 
        .y = pos->y, 
        .w = texture->width, 
        .h = texture->height
    };
    if (SDL_RenderCopy(renderer,texture->texture, NULL, &dest_rect) != 0) {
        fprintf(stderr, "SDL_RenderCopy failed to render text: %s\n", SDL_GetError());
    }
}

void destory_TextTexture (TextTexture *txt_texture) {
    if(txt_texture && txt_texture->texture) {
        SDL_DestroyTexture(txt_texture->texture);
        txt_texture->texture = NULL;
    }
}
