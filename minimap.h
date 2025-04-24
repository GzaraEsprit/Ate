#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL/SDL.h>
#include "game.h"

typedef struct {
    SDL_Surface *mini_bg;
    SDL_Rect position;
    int scaling_factor;
    Uint32 player_color;
    Uint32 platform_color;
    Uint32 movable_color;
    Uint32 destructible_color;
} Minimap;

void initMinimap(Minimap *m, int width, int height, int scaling, int pos_x, int pos_y);
void updateMinimap(Minimap *m, GameState *game);
void drawMinimap(SDL_Surface *screen, Minimap *m);
void freeMinimap(Minimap *m);

#endif


