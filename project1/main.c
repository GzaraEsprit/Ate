// ==== main.c ====
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include "ennemi.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720
#define FPS 60

SDL_Surface *screen = NULL;
SDL_Surface *background1 = NULL;
SDL_Surface *background2 = NULL;
Mix_Chunk *attack_sound = NULL;
Mix_Chunk *hit_sound = NULL;
SDL_Surface *troop_sheet = NULL;
SDL_Surface *hyenas_sheet = NULL;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("SDL Init Error: %s\n", SDL_GetError());
        return 1;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) {
        printf("Video mode error: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    SDL_WM_SetCaption("Enhanced Game", NULL);

    background1 = IMG_Load("back11.png");
    background2 = IMG_Load("back12.png");
    troop_sheet = IMG_Load("troop7.png");
    hyenas_sheet = IMG_Load("hyenas.png");

    attack_sound = Mix_LoadWAV("attack4.wav");
    hit_sound = Mix_LoadWAV("hit4.wav");

    personnage p;
    initialiser_perso(&p);

    enemie E1, E2;
    int usingTroop = 1;
    SDL_Surface *current_bg = background1;

    init_enemie(&E1, 510, troop_sheet);
    init_enemie(&E2, 800, troop_sheet);

    SDL_Event event;
    int done = 1;
    Uint32 start, end, frame;

    while (done) {
        start = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                done = 0;
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        p.perso_pos.x += 20;
                        break;
                    case SDLK_LEFT:
                        p.perso_pos.x -= 20;
                        break;
                    case SDLK_SPACE:
                        Mix_PlayChannel(-1, attack_sound, 0);
                        if (collision(p.perso_pos, E1.pos)) {
                            E1.health -= 10;
                            Mix_PlayChannel(-1, hit_sound, 0);
                        }
                        if (collision(p.perso_pos, E2.pos)) {
                            E2.health -= 10;
                            Mix_PlayChannel(-1, hit_sound, 0);
                        }
                        break;
                    case SDLK_b:
                        usingTroop = !usingTroop;
                        current_bg = usingTroop ? background1 : background2;
                        init_enemie(&E1, 510, usingTroop ? troop_sheet : hyenas_sheet);
                        init_enemie(&E2, 800, usingTroop ? troop_sheet : hyenas_sheet);
                        break;
                }
            }
        }

        SDL_BlitSurface(current_bg, NULL, screen, NULL);

        if (E1.health > 0) {
            deplacerIA(&E1, p.perso_pos);
            animate_enemie(&E1);
            afficher_enemie(&E1, screen);
            draw_health_bar(&E1, screen);
        }

        if (E2.health > 0) {
            deplacerIA(&E2, p.perso_pos);
            animate_enemie(&E2);
            afficher_enemie(&E2, screen);
            draw_health_bar(&E2, screen);
        }

        afficher_perso(&p, screen);
        SDL_Flip(screen);

        end = SDL_GetTicks();
        frame = end - start;
        if (frame < 1000 / FPS)
            SDL_Delay(1000 / FPS - frame);
    }

    SDL_FreeSurface(background1);
    SDL_FreeSurface(background2);
    SDL_FreeSurface(troop_sheet);
    SDL_FreeSurface(hyenas_sheet);
    Mix_FreeChunk(attack_sound);
    Mix_FreeChunk(hit_sound);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

