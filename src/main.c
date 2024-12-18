#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <stdint.h>
#include "include/db/db.h"

int main(void) {
    sqlite3 *db_handle = init_db_engine("./assets/i_chinese.db");
    if (!db_handle) {
        printf("DB Handle not created");
        return 1;
    }
    if (validate_db(db_handle) != SQLITE_OK) {
        fprintf(stderr, "Invalid DB please check DB file.\n");
        close_db_engine(db_handle);
        return 1;
    }

    // Attempt to initialize graphics and timer system.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "I _ Chinese",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_RESIZABLE|SDL_WINDOW_MAXIMIZED
    );
    if (!window) {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Keep the window open, in this case SDL_Delay(5000); statement won't work.
    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
                break;
            }
        }
     }

    // clean up resources before exiting.
    close_db_engine(db_handle);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
