// ==== ennemi.h ====
#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

// Animation states
typedef enum {
    IDLE,
    WALK,
    ATTACK
} EnemyState;

typedef struct enemie {
    SDL_Surface *spritesheet;
    SDL_Surface *spritesheet_alt;
    int direction; // 0 = right, 1 = left
    int health;
    SDL_Rect pos, xminimale, xmaximale;
    SDL_Rect posspritesheet;
    EnemyState state;
} enemie;

typedef struct {
    SDL_Surface *perso;
    SDL_Rect perso_pos;
} personnage;

void init_enemie(enemie *E, int x_start, SDL_Surface *sheet);
void afficher_enemie(enemie *E, SDL_Surface *screen);
void animate_enemie(enemie *E);
void deplacerIA(enemie *E, SDL_Rect posPerso);
int collision(SDL_Rect A, SDL_Rect B);
void initialiser_perso(personnage *p);
void afficher_perso(personnage *p, SDL_Surface *screen);
void draw_health_bar(enemie *E, SDL_Surface *screen);

#endif // HEADER_H_INCLUDED

