#ifndef COMMON_H
#define COMMON_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL_gfxPrimitives.h>
#include <time.h>
#include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 150
#define MINIMAP_SCALE 0.15625 // 1/6.4, pour une carte de 1280x960

typedef enum {
    WAITING,
    WALKING,
    JUMP,
    DOUBLEJUMP,
    DUCK,
    ATTACKING,
    HIT,
    DIE
} State;

typedef enum {
    MODE_JEU,
    MODE_ENIGME
} GameMode;

typedef struct {
    SDL_Surface *hero_d;
    SDL_Surface *hero_g;
    SDL_Surface *bar_score;
    SDL_Surface *bar_health;
    SDL_Rect pos_hero;
    SDL_Rect pos_vie;
    SDL_Rect pos_score;
    SDL_Rect annimation_hero_d[8][8];
    SDL_Rect annimation_hero_g[8][8];
    int score;
    int health;
    int death;
    int direction;
    int vitesse;
    int jump;
    int jump_count;
    int acceleration;
    float velocity_y;
    State state;
    int frame_w;
    int frame_wl;
    int frame_j;
    int frame_dj;
    int frame_a;
    int frame_a2;
    int frame_h;
    int frame_d;
    int frame_du;
    TTF_Font *police;
} Personne;

typedef struct {
    SDL_Surface *mini_bg;
    SDL_Rect position;
    int scaling_factor;
    Uint32 player1_color;
    Uint32 player2_color;
} Minimap;

typedef struct {
    SDL_Surface *screen;
    int quitter;
    GameMode mode;
    Minimap minimap;
    int volume;         // Ajouté
    int fullscreen;     // Ajouté
} GameState;

void initSDL(GameState *state);
void cleanupSDL(GameState *state);

#endif
