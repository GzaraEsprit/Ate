// ==== ennemi.c ====
#include "ennemi.h"
#include <stdio.h>

void init_enemie(enemie *E, int x_start, SDL_Surface *sheet) {
    E->spritesheet = sheet;
    E->pos.x = x_start;
    E->pos.y = 620;
    E->direction = 0;
    E->health = 100;
    E->state = WALK;

    E->posspritesheet.x = 0;
    E->posspritesheet.y = 0;
    E->posspritesheet.h = 100;
    E->posspritesheet.w = 100;

    E->xminimale.x = x_start - 50;
    E->xmaximale.x = x_start + 200;
}

void afficher_enemie(enemie *E, SDL_Surface *screen) {
    SDL_BlitSurface(E->spritesheet, &E->posspritesheet, screen, &E->pos);
}

void animate_enemie(enemie *E) {
    int row = E->state;
    E->posspritesheet.y = row * E->posspritesheet.h;

    static int frame_counter = 0;
    frame_counter++;
    if (frame_counter % 6 == 0) { // slower animation
        if (E->posspritesheet.x >= 300)
            E->posspritesheet.x = 0;
        else
            E->posspritesheet.x += E->posspritesheet.w;
    }
}

void deplacerIA(enemie *E, SDL_Rect posPerso) {
    int distance = E->pos.x - posPerso.x;
    if (distance < 200 && distance > 80) {
        E->direction = 1;
        E->pos.x -= 2;
        E->state = WALK;
    } else if (distance < -80 && distance > -200) {
        E->direction = 0;
        E->pos.x += 2;
        E->state = WALK;
    } else if (collision(E->pos, posPerso)) {
        E->state = ATTACK;
    } else {
        E->state = IDLE;
    }
}

int collision(SDL_Rect A, SDL_Rect B) {
    return !(B.x + B.w < A.x || B.x > A.x + A.w || B.y + B.h < A.y || B.y > A.y + A.h);
}

void initialiser_perso(personnage *p) {
    p->perso = IMG_Load("perso7.png");
    if (!p->perso) {
        printf("Error loading player sprite: %s\n", IMG_GetError());
    }
    p->perso_pos.x = 100;
    p->perso_pos.y = 620;
    p->perso_pos.h = 100;
    p->perso_pos.w = 100;
}

void afficher_perso(personnage *p, SDL_Surface *screen) {
    SDL_BlitSurface(p->perso, NULL, screen, &p->perso_pos);
}

void draw_health_bar(enemie *E, SDL_Surface *screen) {
    SDL_Rect red = {E->pos.x, E->pos.y - 10, 100, 5};
    SDL_Rect green = {E->pos.x, E->pos.y - 10, E->health, 5};
    SDL_FillRect(screen, &red, SDL_MapRGB(screen->format, 255, 0, 0));
    SDL_FillRect(screen, &green, SDL_MapRGB(screen->format, 0, 255, 0));
}
