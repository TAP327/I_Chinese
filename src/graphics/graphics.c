#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "include/graphics/graphics.h"
#include <SDL_rwops.h>
#include <zlib.h>


void set_bg(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 60, 215);
    SDL_RenderClear(renderer);
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

Position get_proportional_pos(SDL_Window *window, const float down_shift, const float right_shift) {
    Position pos = {
        0,
        0
    };
    
    SDL_DisplayMode DM;
    if (SDL_GetCurrentDisplayMode(0, &DM) == 0) {
        int hs_h = DM.h;
        int hs_w = DM.w;
        //SDL_GetWindowSize(window, &h, &w);
        

        printf("home screen HxW: %dx", hs_h);
        printf("%d\n", hs_w);

        pos.x = (int)(hs_w*right_shift);
        pos.y = (int)(hs_h*down_shift);   
    }
    else {
        printf("Home screen dimensions not found.");
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
