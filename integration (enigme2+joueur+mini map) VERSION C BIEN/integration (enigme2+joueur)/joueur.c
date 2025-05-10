#include "joueur.h"
#include <stdio.h>

void initPerso(Personne *p) {
    if (!p) return;
    p->hero_d = IMG_Load("image/heroD.png");
    if (!p->hero_d) {
        printf("Erreur: Impossible de charger image/heroD.png: %s\n", IMG_GetError());
        p->hero_d = SDL_CreateRGBSurface(SDL_SWSURFACE, 40, 70, 32, 0, 0, 0, 0);
        if (!p->hero_d) {
            printf("Erreur: Impossible de créer une surface par défaut pour hero_d\n");
            return;
        }
        SDL_FillRect(p->hero_d, NULL, SDL_MapRGB(p->hero_d->format, 255, 0, 0));
    }
    p->hero_g = IMG_Load("image/heroG.png");
    if (!p->hero_g) {
        printf("Erreur: Impossible de charger image/heroG.png: %s\n", IMG_GetError());
        p->hero_g = SDL_CreateRGBSurface(SDL_SWSURFACE, 40, 70, 32, 0, 0, 0, 0);
        if (!p->hero_g) {
            printf("Erreur: Impossible de créer une surface par défaut pour hero_g\n");
            SDL_FreeSurface(p->hero_d);
            p->hero_d = NULL;
            return;
        }
        SDL_FillRect(p->hero_g, NULL, SDL_MapRGB(p->hero_g->format, 0, 255, 0));
    }
    p->bar_score = NULL;
    p->bar_health = NULL;
    p->pos_vie.x = 50;
    p->pos_vie.y = 50;
    p->pos_score.x = 380;
    p->pos_score.y = 50;
    p->score = 0;
    p->health = 100;
    p->death = 0;
    p->direction = 0;
    p->vitesse = 200;
    p->jump = 400;
    p->jump_count = 0;
    p->acceleration = 0;
    p->velocity_y = 0;
    p->state = WAITING;
    p->pos_hero.x = 60;
    p->pos_hero.y = 502;
    p->pos_hero.w = 40;
    p->pos_hero.h = 70;
    p->frame_w = p->frame_wl = p->frame_j = p->frame_dj = p->frame_a = p->frame_a2 = p->frame_h = p->frame_d = p->frame_du = 0;
    p->police = TTF_OpenFont("ttf_police/School & COLLEGE Outline.ttf", 20);
    if (!p->police) {
        printf("Erreur: Impossible de charger ttf_police/School & COLLEGE Outline.ttf: %s\n", TTF_GetError());
        SDL_FreeSurface(p->hero_d);
        SDL_FreeSurface(p->hero_g);
        p->hero_d = NULL;
        p->hero_g = NULL;
        return;
    }
    for (int i = 0; i < 4; i++) {
        p->annimation_hero_d[WAITING][i].x = (10 + (i * 60));
        p->annimation_hero_d[WAITING][i].y = 0;
        p->annimation_hero_d[WAITING][i].w = 60;
        p->annimation_hero_d[WAITING][i].h = 85;
    }
    for (int i = 0; i < 8; i++) {
        p->annimation_hero_d[WALKING][i].x = (10 + (i * 62));
        p->annimation_hero_d[WALKING][i].y = 100;
        p->annimation_hero_d[WALKING][i].w = 60;
        p->annimation_hero_d[WALKING][i].h = 85;
    }
    for (int i = 0; i < 4; i++) {
        p->annimation_hero_d[DUCK][i].x = (10 + (i * 60));
        p->annimation_hero_d[DUCK][i].y = 200;
        p->annimation_hero_d[DUCK][i].w = 60;
        p->annimation_hero_d[DUCK][i].h = 60;
    }
    for (int i = 0; i < 4; i++) {
        p->annimation_hero_d[JUMP][i].x = (10 + (i * 60));
        p->annimation_hero_d[JUMP][i].y = 300;
        p->annimation_hero_d[JUMP][i].w = 60;
        p->annimation_hero_d[JUMP][i].h = 85;
    }
    for (int i = 0; i < 4; i++) {
        p->annimation_hero_d[DOUBLEJUMP][i].x = (10 + (i * 60));
        p->annimation_hero_d[DOUBLEJUMP][i].y = 300;
        p->annimation_hero_d[DOUBLEJUMP][i].w = 60;
        p->annimation_hero_d[DOUBLEJUMP][i].h = 85;
    }
    for (int i = 0; i < 4; i++) {
        p->annimation_hero_g[WAITING][i].x = (450 - (i * 60));
        p->annimation_hero_g[WAITING][i].y = 0;
        p->annimation_hero_g[WAITING][i].w = 60;
        p->annimation_hero_g[WAITING][i].h = 85;
    }
    for (int i = 0; i < 8; i++) {
        p->annimation_hero_g[WALKING][i].x = (450 - (i * 62));
        p->annimation_hero_g[WALKING][i].y = 100;
        p->annimation_hero_g[WALKING][i].w = 60;
        p->annimation_hero_g[WALKING][i].h = 85;
    }
    for (int i = 0; i < 4; i++) {
        p->annimation_hero_g[DUCK][i].x = (450 - (i * 60));
        p->annimation_hero_g[DUCK][i].y = 200;
        p->annimation_hero_g[DUCK][i].w = 60;
        p->annimation_hero_g[DUCK][i].h = 60;
    }
    for (int i = 0; i < 4; i++) {
        p->annimation_hero_g[JUMP][i].x = (450 - (i * 60));
        p->annimation_hero_g[JUMP][i].y = 300;
        p->annimation_hero_g[JUMP][i].w = 60;
        p->annimation_hero_g[JUMP][i].h = 85;
    }
    for (int i = 0; i < 4; i++) {
        p->annimation_hero_g[DOUBLEJUMP][i].x = (450 - (i * 60));
        p->annimation_hero_g[DOUBLEJUMP][i].y = 300;
        p->annimation_hero_g[DOUBLEJUMP][i].w = 60;
        p->annimation_hero_g[DOUBLEJUMP][i].h = 85;
    }
}

void initPerso2(Personne *p2) {
    if (!p2) return;
    p2->hero_d = IMG_Load("image/heroD.png");
    if (!p2->hero_d) {
        printf("Erreur: Impossible de charger image/heroD.png: %s\n", IMG_GetError());
        p2->hero_d = SDL_CreateRGBSurface(SDL_SWSURFACE, 40, 70, 32, 0, 0, 0, 0);
        if (!p2->hero_d) {
            printf("Erreur: Impossible de créer une surface par défaut pour hero_d\n");
            return;
        }
        SDL_FillRect(p2->hero_d, NULL, SDL_MapRGB(p2->hero_d->format, 255, 0, 0));
    }
    p2->hero_g = IMG_Load("image/heroG.png");
    if (!p2->hero_g) {
        printf("Erreur: Impossible de charger image/heroG.png: %s\n", IMG_GetError());
        p2->hero_g = SDL_CreateRGBSurface(SDL_SWSURFACE, 40, 70, 32, 0, 0, 0, 0);
        if (!p2->hero_g) {
            printf("Erreur: Impossible de créer une surface par défaut pour hero_g\n");
            SDL_FreeSurface(p2->hero_d);
            p2->hero_d = NULL;
            return;
        }
        SDL_FillRect(p2->hero_g, NULL, SDL_MapRGB(p2->hero_g->format, 0, 255, 0));
    }
    p2->bar_score = NULL;
    p2->bar_health = NULL;
    p2->pos_vie.x = 600;
    p2->pos_vie.y = 50;
    p2->pos_score.x = 700;
    p2->pos_score.y = 50;
    p2->score = 0;
    p2->health = 100;
    p2->death = 0;
    p2->direction = 0;
    p2->vitesse = 200;
    p2->jump = 400;
    p2->jump_count = 0;
    p2->acceleration = 0;
    p2->velocity_y = 0;
    p2->state = WAITING;
    p2->pos_hero.x = 400;
    p2->pos_hero.y = 502;
    p2->pos_hero.w = 40;
    p2->pos_hero.h = 70;
    p2->frame_w = p2->frame_wl = p2->frame_j = p2->frame_dj = p2->frame_a = p2->frame_a2 = p2->frame_h = p2->frame_d = p2->frame_du = 0;
    p2->police = TTF_OpenFont("ttf_police/School & COLLEGE Outline.ttf", 20);
    if (!p2->police) {
        printf("Erreur: Impossible de charger ttf_police/School & COLLEGE Outline.ttf: %s\n", TTF_GetError());
        SDL_FreeSurface(p2->hero_d);
        SDL_FreeSurface(p2->hero_g);
        p2->hero_d = NULL;
        p2->hero_g = NULL;
        return;
    }
    for (int i = 0; i < 4; i++) {
        p2->annimation_hero_d[WAITING][i].x = (10 + (i * 60));
        p2->annimation_hero_d[WAITING][i].y = 0;
        p2->annimation_hero_d[WAITING][i].w = 60;
        p2->annimation_hero_d[WAITING][i].h = 85;
    }
    for (int i = 0; i < 8; i++) {
        p2->annimation_hero_d[WALKING][i].x = (10 + (i * 62));
        p2->annimation_hero_d[WALKING][i].y = 100;
        p2->annimation_hero_d[WALKING][i].w = 60;
        p2->annimation_hero_d[WALKING][i].h = 85;
    }
    for (int i = 0; i < 4; i++) {
        p2->annimation_hero_d[DUCK][i].x = (10 + (i * 60));
        p2->annimation_hero_d[DUCK][i].y = 200;
        p2->annimation_hero_d[DUCK][i].w = 60;
        p2->annimation_hero_d[DUCK][i].h = 60;
    }
    for (int i = 0; i < 4; i++) {
        p2->annimation_hero_d[JUMP][i].x = (10 + (i * 60));
        p2->annimation_hero_d[JUMP][i].y = 300;
        p2->annimation_hero_d[JUMP][i].w = 60;
        p2->annimation_hero_d[JUMP][i].h = 85;
    }
    for (int i = 0; i < 4; i++) {
        p2->annimation_hero_d[DOUBLEJUMP][i].x = (10 + (i * 60));
        p2->annimation_hero_d[DOUBLEJUMP][i].y = 300;
        p2->annimation_hero_d[DOUBLEJUMP][i].w = 60;
        p2->annimation_hero_d[DOUBLEJUMP][i].h = 85;
    }
    for (int i = 0; i < 4; i++) {
        p2->annimation_hero_g[WAITING][i].x = (450 - (i * 60));
        p2->annimation_hero_g[WAITING][i].y = 0;
        p2->annimation_hero_g[WAITING][i].w = 60;
        p2->annimation_hero_g[WAITING][i].h = 85;
    }
    for (int i = 0; i < 8; i++) {
        p2->annimation_hero_g[WALKING][i].x = (450 - (i * 62));
        p2->annimation_hero_g[WALKING][i].y = 100;
        p2->annimation_hero_g[WALKING][i].w = 60;
        p2->annimation_hero_g[WALKING][i].h = 85;
    }
    for (int i = 0; i < 4; i++) {
        p2->annimation_hero_g[DUCK][i].x = (450 - (i * 60));
        p2->annimation_hero_g[DUCK][i].y = 200;
        p2->annimation_hero_g[DUCK][i].w = 60;
        p2->annimation_hero_g[DUCK][i].h = 60;
    }
    for (int i = 0; i < 4; i++) {
        p2->annimation_hero_g[JUMP][i].x = (450 - (i * 60));
        p2->annimation_hero_g[JUMP][i].y = 300;
        p2->annimation_hero_g[JUMP][i].w = 60;
        p2->annimation_hero_g[JUMP][i].h = 85;
    }
    for (int i = 0; i < 4; i++) {
        p2->annimation_hero_g[DOUBLEJUMP][i].x = (450 - (i * 60));
        p2->annimation_hero_g[DOUBLEJUMP][i].y = 300;
        p2->annimation_hero_g[DOUBLEJUMP][i].w = 60;
        p2->annimation_hero_g[DOUBLEJUMP][i].h = 85;
    }
}

void handleEventsJoueur(GameState *state, Personne *perso, Personne *perso2, Mix_Chunk *attack) {
    if (!state || !perso || !perso2) return;
    SDL_Event event;
    int key_pressed = 0;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                state->quitter = 1;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    state->quitter = 1;
                } else if (event.key.keysym.sym == SDLK_p) {
                    printf("Touche P appuyée, passage au mode énigme\n");
                    state->mode = MODE_ENIGME;
                } else if (event.key.keysym.sym == SDLK_x && attack) {
                    Mix_PlayChannel(-1, attack, 0);
                } else if (event.key.keysym.sym == SDLK_a) {
                    perso2->pos_hero.x = 400;
                }
                break;
        }
    }
    const Uint8 *key = SDL_GetKeyState(NULL);
    if (!perso->death) {
        if (key[SDLK_UP] && (perso->jump_count >= 0 && perso->jump_count <= 1) &&
            (perso->pos_hero.y <= 502 && perso->pos_hero.y >= 362)) {
            perso->jump_count++;
            saut(perso, 1.0f / 60.0f);
            perso->score += 3;
            printf("Perso1 - Saut, État: %d, Frame_wl: %d\n", perso->state, perso->frame_wl);
        }
        if (key[SDLK_RIGHT]) {
            key_pressed = 1;
            if (perso->state != JUMP && perso->state != DOUBLEJUMP && perso->state != DUCK && perso->state != ATTACKING) {
                if (perso->state != WALKING) {
                    perso->frame_wl = 0;
                }
                perso->state = WALKING;
                printf("Perso1 DROITE - État: %d, Frame_wl: %d\n", perso->state, perso->frame_wl);
            }
            perso->direction = 0;
            deplacerPerso(perso, 1.0f / 60.0f);
            perso->score += 1;
        }
        if (key[SDLK_LEFT]) {
            key_pressed = 1;
            if (perso->state != JUMP && perso->state != DOUBLEJUMP && perso->state != DUCK && perso->state != ATTACKING) {
                if (perso->state != WALKING) {
                    perso->frame_wl = 0;
                }
                perso->state = WALKING;
                printf("Perso1 GAUCHE - État: %d, Frame_wl: %d\n", perso->state, perso->frame_wl);
            }
            perso->direction = 1;
            deplacerPerso(perso, 1.0f / 60.0f);
            perso->score += 1;
        }
        if (key[SDLK_DOWN]) {
            if (perso->frame_du == 1) perso->frame_du = 0;
            perso->state = DUCK;
            perso->pos_hero.h = 50;
            perso->pos_hero.y = 502 + (70 - 50);
            printf("Perso1 - Accroupi, État: %d, Frame_wl: %d\n", perso->state, perso->frame_wl);
        } else if (perso->state == DUCK) {
            perso->state = WAITING;
            perso->pos_hero.h = 70;
            perso->pos_hero.y = 502;
            printf("Perso1 - Fin accroupi, État: %d, Frame_wl: %d\n", perso->state, perso->frame_wl);
        }
        if (key[SDLK_x] && perso->state != WALKING) {
            perso->state = ATTACKING;
            if (perso->direction == 0) perso->pos_hero.x += 2;
            else if (perso->direction == 1) perso->pos_hero.x -= 2;
            perso->score += 2;
            printf("Perso1 - Attaque, État: %d, Frame_wl: %d\n", perso->state, perso->frame_wl);
        }
        if (key[SDLK_SPACE]) {
            if (perso->acceleration <= 50) perso->acceleration += 10;
            printf("Perso1 - Accélération: %d\n", perso->acceleration);
        } else {
            perso->acceleration = 0;
        }
        if (key[SDLK_h]) {
            perso->state = HIT;
            perso->health -= 10;
            printf("Perso1 - Touché, État: %d, Frame_wl: %d\n", perso->state, perso->frame_wl);
        }
        if (key[SDLK_m]) {
            perso->state = DIE;
            perso->death = 1;
            perso->health = 0;
            printf("Perso1 - Mort, État: %d, Frame_wl: %d\n", perso->state, perso->frame_wl);
        }
        if (key[SDLK_l]) {
            perso->score += 17;
        }
    }
    if (!perso2->death) {
        if (key[SDLK_z] && (perso2->jump_count >= 0 && perso2->jump_count <= 1) &&
            (perso2->pos_hero.y <= 502 && perso2->pos_hero.y >= 362)) {
            perso2->jump_count++;
            saut(perso2, 1.0f / 60.0f);
            perso2->score += 3;
            printf("Perso2 - Saut, État: %d, Frame_wl: %d\n", perso2->state, perso2->frame_wl);
        }
        if (key[SDLK_d]) {
            key_pressed = 1;
            if (perso2->state != JUMP && perso2->state != DOUBLEJUMP && perso2->state != DUCK && perso2->state != ATTACKING) {
                if (perso2->state != WALKING) {
                    perso2->frame_wl = 0;
                }
                perso2->state = WALKING;
                printf("Perso2 DROITE - État: %d, Frame_wl: %d\n", perso2->state, perso2->frame_wl);
            }
            perso2->direction = 0;
            deplacerPerso(perso2, 1.0f / 60.0f);
            perso2->score += 1;
        }
        if (key[SDLK_q]) {
            key_pressed = 1;
            if (perso2->state != JUMP && perso2->state != DOUBLEJUMP && perso2->state != DUCK && perso2->state != ATTACKING) {
                if (perso2->state != WALKING) {
                    perso2->frame_wl = 0;
                }
                perso2->state = WALKING;
                printf("Perso2 GAUCHE - État: %d, Frame_wl: %d\n", perso2->state, perso2->frame_wl);
            }
            perso2->direction = 1;
            deplacerPerso(perso2, 1.0f / 60.0f);
            perso2->score += 1;
        }
        if (key[SDLK_s]) {
            if (perso2->frame_du == 1) perso2->frame_du = 0;
            perso2->state = DUCK;
            perso2->pos_hero.h = 50;
            perso2->pos_hero.y = 502 + (70 - 50);
            printf("Perso2 - Accroupi, État: %d, Frame_wl: %d\n", perso2->state, perso2->frame_wl);
        } else if (perso2->state == DUCK) {
            perso2->state = WAITING;
            perso2->pos_hero.h = 70;
            perso2->pos_hero.y = 502;
            printf("Perso2 - Fin accroupi, État: %d, Frame_wl: %d\n", perso2->state, perso2->frame_wl);
        }
        if (key[SDLK_y] && perso2->state != WALKING) {
            perso2->state = ATTACKING;
            if (perso2->direction == 0) perso2->pos_hero.x += 2;
            else if (perso2->direction == 1) perso2->pos_hero.x -= 2;
            perso2->score += 2;
            printf("Perso2 - Attaque, État: %d, Frame_wl: %d\n", perso2->state, perso2->frame_wl);
        }
        if (key[SDLK_p]) {
            if (perso2->acceleration <= 50) perso2->acceleration += 10;
            printf("Perso2 - Accélération: %d\n", perso2->acceleration);
        } else {
            perso2->acceleration = 0;
        }
        if (key[SDLK_r]) {
            perso2->state = HIT;
            perso2->health -= 10;
            printf("Perso2 - Touché, État: %d, Frame_wl: %d\n", perso2->state, perso2->frame_wl);
        }
        if (key[SDLK_o]) {
            perso2->state = DIE;
            perso2->death = 1;
            perso2->health = 0;
            printf("Perso2 - Mort, État: %d, Frame_wl: %d\n", perso2->state, perso2->frame_wl);
        }
        if (key[SDLK_n]) {
            perso2->score += 17;
        }
    }
    if (!key_pressed) {
        if (perso->state != JUMP && perso->state != DOUBLEJUMP && perso->state != DIE && perso->state != DUCK && perso->state != ATTACKING) {
            perso->state = WAITING;
            printf("Perso1 - Aucun déplacement, État: %d, Frame_wl: %d\n", perso->state, perso->frame_wl);
        }
        if (perso2->state != JUMP && perso2->state != DOUBLEJUMP && perso2->state != DIE && perso2->state != DUCK && perso2->state != ATTACKING) {
            perso2->state = WAITING;
            printf("Perso2 - Aucun déplacement, État: %d, Frame_wl: %d\n", perso2->state, perso2->frame_wl);
        }
    }
}

void updateJoueur(Personne *perso, Personne *perso2, float deltaTime) {
    if (!perso || !perso2) return;
    gravity(perso, deltaTime);
    gravity(perso2, deltaTime);
    if (perso->health <= 0) {
        perso->death = 1;
        perso->state = DIE;
        printf("Perso1 - Santé à 0, État: %d, Frame_wl: %d\n", perso->state, perso->frame_wl);
    }
    if (perso2->health <= 0) {
        perso2->death = 1;
        perso2->state = DIE;
        printf("Perso2 - Santé à 0, État: %d, Frame_wl: %d\n", perso2->state, perso2->frame_wl);
    }
}

void renderJoueur(GameState *state, Personne *perso, Personne *perso2, SDL_Surface *map) {
    if (!state || !state->screen || !perso || !perso2 || !map) return;
    SDL_BlitSurface(map, NULL, state->screen, &(SDL_Rect){0, 0, 0, 0});
    animerPerso(perso);
    animerPerso(perso2);
    afficherPerso(*perso, state->screen);
    afficherPerso(*perso2, state->screen);
    afficherScore_vie(*perso, state->screen);
    afficherScore_vie(*perso2, state->screen);
    updateMinimap(&state->minimap, perso, perso2);
    drawMinimap(state->screen, &state->minimap);
}

void cleanupJoueur(GameState *state, Personne *perso, Personne *perso2, Mix_Music *musique, Mix_Chunk *attack, SDL_Surface *map) {
    if (perso) free_perso(perso);
    if (perso2) free_perso(perso2);
    if (musique) Mix_FreeMusic(musique);
    if (attack) Mix_FreeChunk(attack);
    if (map) SDL_FreeSurface(map);
    if (state) freeMinimap(&state->minimap);
}

void animerPerso(Personne *p) {
    if (!p) return;
    static int frameCounter = 0;
    frameCounter++;
    printf("AnimerPerso %s - FrameCounter: %d\n", (p->pos_hero.x == 60) ? "Perso1" : "Perso2", frameCounter);
    if (frameCounter >= 8) {
        if ((p->direction == 0 || p->direction == 1) && p->state == WAITING) {
            p->frame_w++;
            if (p->frame_w >= 4) p->frame_w = 0;
            printf("AnimerPerso %s - État: WAITING, Frame_w: %d\n", (p->pos_hero.x == 60) ? "Perso1" : "Perso2", p->frame_w);
        }
        if ((p->direction == 0 || p->direction == 1) && p->state == WALKING) {
            p->frame_wl++;
            if (p->frame_wl >= 8) p->frame_wl = 0;
            printf("AnimerPerso %s - État: WALKING, Frame_wl: %d\n", (p->pos_hero.x == 60) ? "Perso1" : "Perso2", p->frame_wl);
        }
        if ((p->direction == 0 || p->direction == 1) && p->state == DUCK) {
            p->frame_du++;
            if (p->frame_du >= 4) p->frame_du = 0;
            printf("AnimerPerso %s - État: DUCK, Frame_du: %d\n", (p->pos_hero.x == 60) ? "Perso1" : "Perso2", p->frame_du);
        }
        if ((p->direction == 0 || p->direction == 1) && (p->state == JUMP || p->state == DOUBLEJUMP)) {
            p->frame_j++;
            if (p->frame_j >= 4) p->frame_j = 0;
            printf("AnimerPerso %s - État: JUMP/DOUBLEJUMP, Frame_j: %d\n", (p->pos_hero.x == 60) ? "Perso1" : "Perso2", p->frame_j);
        }
        frameCounter = 0;
    }
}

void deplacerPerso(Personne *p, float deltaTime) {
    if (!p) return;
    float moveSpeed = (p->vitesse + p->acceleration) * deltaTime;
    if (p->direction == 0) {
        p->pos_hero.x += moveSpeed;
        if (p->pos_hero.x > SCREEN_WIDTH - p->pos_hero.w) p->pos_hero.x = SCREEN_WIDTH - p->pos_hero.w;
    } else if (p->direction == 1) {
        p->pos_hero.x -= moveSpeed;
        if (p->pos_hero.x < 0) p->pos_hero.x = 0;
    }
    printf("DeplacerPerso %s - Position: %d, Vitesse: %d, Acceleration: %d\n",
           (p->pos_hero.x == 60) ? "Perso1" : "Perso2", p->pos_hero.x, p->vitesse, p->acceleration);
}

void saut(Personne *p, float deltaTime) {
    if (!p) return;
    if (p->jump_count == 1 || p->jump_count == 2) {
        p->velocity_y = -p->jump;
        p->state = (p->jump_count == 1) ? JUMP : DOUBLEJUMP;
    }
}

void gravity(Personne *p, float deltaTime) {
    if (!p) return;
    if (p->pos_hero.y < 502 || p->velocity_y != 0) {
        p->velocity_y += 800 * deltaTime;
        p->pos_hero.y += p->velocity_y * deltaTime;
    }
    if (p->pos_hero.y >= 502) {
        p->pos_hero.y = 502;
        p->velocity_y = 0;
        if (p->state == JUMP || p->state == DOUBLEJUMP) {
            p->state = WAITING;
            p->jump_count = 0;
            printf("Perso %s - Atterrissage, État: %d, Frame_wl: %d\n",
                   (p->pos_hero.x == 60) ? "Perso1" : "Perso2", p->state, p->frame_wl);
        }
    }
}

void afficherPerso(Personne p, SDL_Surface *screen_p) {
    if (!screen_p || !p.hero_d || !p.hero_g) return;
    if (p.direction == 0 && p.state == WAITING && p.frame_w < 4) {
        SDL_BlitSurface(p.hero_d, &p.annimation_hero_d[WAITING][p.frame_w], screen_p, &p.pos_hero);
        printf("AfficherPerso %s DROITE - État: WAITING, Frame_w: %d\n", (p.pos_hero.x == 60) ? "Perso1" : "Perso2", p.frame_w);
    } else if (p.direction == 1 && p.state == WAITING && p.frame_w < 4) {
        SDL_BlitSurface(p.hero_g, &p.annimation_hero_g[WAITING][p.frame_w], screen_p, &p.pos_hero);
        printf("AfficherPerso %s GAUCHE - État: WAITING, Frame_w: %d\n", (p.pos_hero.x == 60) ? "Perso1" : "Perso2", p.frame_w);
    } else if (p.direction == 0 && p.state == WALKING && p.frame_wl < 8) {
        SDL_BlitSurface(p.hero_d, &p.annimation_hero_d[WALKING][p.frame_wl], screen_p, &p.pos_hero);
        printf("AfficherPerso %s DROITE - État: WALKING, Frame_wl: %d\n", (p.pos_hero.x == 60) ? "Perso1" : "Perso2", p.frame_wl);
    } else if (p.direction == 1 && p.state == WALKING && p.frame_wl < 8) {
        SDL_BlitSurface(p.hero_g, &p.annimation_hero_g[WALKING][p.frame_wl], screen_p, &p.pos_hero);
        printf("AfficherPerso %s GAUCHE - État: WALKING, Frame_wl: %d\n", (p.pos_hero.x == 60) ? "Perso1" : "Perso2", p.frame_wl);
    } else if (p.direction == 0 && p.state == DUCK && p.frame_du < 4) {
        SDL_BlitSurface(p.hero_d, &p.annimation_hero_d[DUCK][p.frame_du], screen_p, &p.pos_hero);
        printf("AfficherPerso %s - État: DUCK, Frame_du: %d\n", (p.pos_hero.x == 60) ? "Perso1" : "Perso2", p.frame_du);
    } else if (p.direction == 1 && p.state == DUCK && p.frame_du < 4) {
        SDL_BlitSurface(p.hero_g, &p.annimation_hero_g[DUCK][p.frame_du], screen_p, &p.pos_hero);
        printf("AfficherPerso %s - État: DUCK, Frame_du: %d\n", (p.pos_hero.x == 60) ? "Perso1" : "Perso2", p.frame_du);
    } else if (p.direction == 0 && (p.state == JUMP || p.state == DOUBLEJUMP) && p.frame_j < 4) {
        SDL_BlitSurface(p.hero_d, &p.annimation_hero_d[JUMP][p.frame_j], screen_p, &p.pos_hero);
        printf("AfficherPerso %s - État: JUMP/DOUBLEJUMP, Frame_j: %d\n", (p.pos_hero.x == 60) ? "Perso1" : "Perso2", p.frame_j);
    } else if (p.direction == 1 && (p.state == JUMP || p.state == DOUBLEJUMP) && p.frame_j < 4) {
        SDL_BlitSurface(p.hero_g, &p.annimation_hero_g[JUMP][p.frame_j], screen_p, &p.pos_hero);
        printf("AfficherPerso %s - État: JUMP/DOUBLEJUMP, Frame_j: %d\n", (p.pos_hero.x == 60) ? "Perso1" : "Perso2", p.frame_j);
    }
}

void afficherScore_vie(Personne p, SDL_Surface *screen_s) {
    if (!screen_s || !p.police) return;
    SDL_Color olive = {13, 91, 225};
    char tab2[80];
    sprintf(tab2, "Health : %d %%", p.health);
    p.bar_health = TTF_RenderText_Blended(p.police, tab2, olive);
    if (p.bar_health) {
        SDL_BlitSurface(p.bar_health, NULL, screen_s, &p.pos_vie);
        SDL_FreeSurface(p.bar_health);
        p.bar_health = NULL;
    }
    char tab[80];
    sprintf(tab, "Score : %d", p.score);
    p.bar_score = TTF_RenderText_Blended(p.police, tab, olive);
    if (p.bar_score) {
        SDL_BlitSurface(p.bar_score, NULL, screen_s, &p.pos_score);
        SDL_FreeSurface(p.bar_score);
        p.bar_score = NULL;
    }
}

void free_perso(Personne *p) {
    if (!p) return;
    if (p->bar_score) {
        SDL_FreeSurface(p->bar_score);
        p->bar_score = NULL;
    }
    if (p->bar_health) {
        SDL_FreeSurface(p->bar_health);
        p->bar_health = NULL;
    }
    if (p->hero_d) {
        SDL_FreeSurface(p->hero_d);
        p->hero_d = NULL;
    }
    if (p->hero_g) {
        SDL_FreeSurface(p->hero_g);
        p->hero_g = NULL;
    }
    if (p->police) {
        TTF_CloseFont(p->police);
        p->police = NULL;
    }
}
