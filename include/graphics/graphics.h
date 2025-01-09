#ifndef _GRAPHICS_H
#define _GRAPHICS_H

void set_bg(SDL_Renderer *renderer);
SDL_Texture *get_txt_texture(SDL_Renderer *renderer, const char *text, SDL_Color *color, const char *file, const int size);
void render_txt(void);

#endif 
