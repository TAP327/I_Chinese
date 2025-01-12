#ifndef _GRAPHICS_H
#define _GRAPHICS_H

typedef struct {
    SDL_Texture *texture;
    int width;
    int height;
} TextTexture;

typedef struct {
    int x;
    int y;
} Position;

void set_bg(SDL_Renderer *renderer);
TextTexture get_txt_texture(SDL_Renderer *renderer, const char *text, SDL_Color *color, const char *file, const int size);
Position get_proportional_pos(int down_shift, int right_shift);
void render_txt(SDL_Renderer *renderer, TextTexture *texture, Position *pos);
void destory_TextTexture (TextTexture *txt_texture);

#endif 
