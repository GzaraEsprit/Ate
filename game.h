#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    int is_movable;
    int is_active;  // For destructible platforms
} Platform;

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    int vel_x;
    int vel_y;
    int is_grounded;
} Player;

typedef struct {
    Player player;
    Platform *platforms;
    int platform_count;
    SDL_Rect camera;
} GameState;

void initGame(GameState *game);
void handleInput(GameState *game);
void updateGame(GameState *game);
void renderGame(SDL_Surface *screen, GameState *game);

#endif
