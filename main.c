#include <SDL/SDL.h>
#include "game.h"
#include "minimap.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char *argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL init failed: %s\n", SDL_GetError());
        return 1;
    }
   
    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if(!screen) {
        printf("Failed to set video mode: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    GameState game;
    initGame(&game);
   
    Minimap minimap;
    initMinimap(&minimap, 2000, 2000, 10, SCREEN_WIDTH - 210, 10);
   
    int running = 1;
    SDL_Event event;
   
    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) running = 0;
        }
       
        handleInput(&game);
        updateGame(&game);
        updateMinimap(&minimap, &game);
       
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        renderGame(screen, &game);
        drawMinimap(screen, &minimap);
       
        SDL_Flip(screen);
        SDL_Delay(16);
    }
   
    freeMinimap(&minimap);
    free(game.platforms);
    SDL_Quit();
    return 0;
}
