#include "enigme.h"

void initEnigme(Puzzle puzzles[], SDL_Surface **background, SDL_Surface **victoryImage, SDL_Surface **defeatImage) {
    srand(time(NULL));
    *background = IMG_Load("assets/background.png");
    *victoryImage = IMG_Load("assets/victory.png");
    *defeatImage = IMG_Load("assets/defeat.png");

    if (!*background) {
        printf("Erreur de chargement du background: %s\n", IMG_GetError());
        *background = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
        SDL_FillRect(*background, NULL, SDL_MapRGB((*background)->format, 100, 149, 237));
    }
    if (!*victoryImage) {
        printf("Warning: Impossible de charger victory.png\n");
        *victoryImage = SDL_CreateRGBSurface(SDL_SWSURFACE, 200, 100, 32, 0, 0, 0, 0);
        SDL_FillRect(*victoryImage, NULL, SDL_MapRGB((*victoryImage)->format, 0, 255, 0));
    }
    if (!*defeatImage) {
        printf("Warning: Impossible de charger defeat.png\n");
        *defeatImage = SDL_CreateRGBSurface(SDL_SWSURFACE, 200, 100, 32, 0, 0, 0, 0);
        SDL_FillRect(*defeatImage, NULL, SDL_MapRGB((*defeatImage)->format, 255, 0, 0));
    }
}

void loadResourcesEnigme(Puzzle puzzles[], int *currentPuzzle, Uint32 *startTime) {
    if (!puzzles || !currentPuzzle || !startTime) {
        printf("Erreur: Arguments nuls dans loadResourcesEnigme\n");
        return;
    }
    for (int i = 0; i < TOTAL_PUZZLES; i++) {
        initPuzzle(&puzzles[i], i);
        if (!puzzles[i].baseImage || !puzzles[i].shadowImage) {
            printf("Erreur: Échec de l'initialisation du puzzle %d\n", i);
        }
    }
    for (int i = TOTAL_PUZZLES - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Puzzle temp = puzzles[i];
        puzzles[i] = puzzles[j];
        puzzles[j] = temp;
    }
    *currentPuzzle = 0;
    printf("Ressources énigme chargées: currentPuzzle=%d\n", *currentPuzzle);
}

void handleEventsEnigme(GameState *state, Puzzle puzzles[], int *currentPuzzle, DragState *drag, Uint32 *startTime, Uint32 maxTime, SDL_Surface *victoryImage, SDL_Surface *defeatImage, Personne *perso, Personne *perso2, SDL_Surface *map) {
    if (!state || !state->screen || !puzzles || !drag || !startTime || !currentPuzzle || !victoryImage || !defeatImage || !perso || !perso2 || !map) {
        printf("Erreur: Arguments nuls dans handleEventsEnigme\n");
        return;
    }
    printf("handleEventsEnigme: currentPuzzle=%d, startTime=%u, maxTime=%u\n", *currentPuzzle, *startTime, maxTime);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            state->quitter = 1;
        } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            state->mode = MODE_JEU;
            printf("Retour au mode jeu via Échap\n");
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            printf("Clic souris: x=%d, y=%d\n", event.button.x, event.button.y);
            for (int i = 0; i < TOTAL_CHOICES; i++) {
                SDL_Rect pos = puzzles[*currentPuzzle].choicePositions[i];
                int choiceWidth = puzzles[*currentPuzzle].choices[i] ? puzzles[*currentPuzzle].choices[i]->w : 100;
                int choiceHeight = puzzles[*currentPuzzle].choices[i] ? puzzles[*currentPuzzle].choices[i]->h : 100;
                printf("Vérification choix %d: x=%d, y=%d, w=%d, h=%d\n", i, pos.x, pos.y, choiceWidth, choiceHeight);
                if (event.button.x >= pos.x && event.button.x <= pos.x + choiceWidth &&
                    event.button.y >= pos.y && event.button.y <= pos.y + choiceHeight) {
                    drag->dragging = 1;
                    drag->draggedIndex = i;
                    drag->offsetX = event.button.x - pos.x;
                    drag->offsetY = event.button.y - pos.y;
                    printf("Début drag: index=%d, offsetX=%d, offsetY=%d\n", i, drag->offsetX, drag->offsetY);
                    break;
                }
            }
        } else if (event.type == SDL_MOUSEMOTION && drag->dragging) {
            puzzles[*currentPuzzle].choicePositions[drag->draggedIndex].x = event.motion.x - drag->offsetX;
            puzzles[*currentPuzzle].choicePositions[drag->draggedIndex].y = event.motion.y - drag->offsetY;
            printf("Drag en cours: x=%d, y=%d\n", event.motion.x, event.motion.y);
        } else if (event.type == SDL_MOUSEBUTTONUP && drag->dragging) {
            printf("Relâchement souris: x=%d, y=%d\n", event.button.x, event.button.y);
            int inZone = checkDrop(&puzzles[*currentPuzzle], event.button.x, event.button.y);
            drag->dragging = 0;
            if (inZone) {
                Uint32 animationStart = SDL_GetTicks();
                int isCorrect = (drag->draggedIndex == puzzles[*currentPuzzle].correctIndex);
                printf("Drop détecté: inZone=%d, isCorrect=%d\n", inZone, isCorrect);
                while (SDL_GetTicks() - animationStart < 1500) {
                    // Rendre le mode joueur en arrière-plan
                    renderJoueur(state, perso, perso2, map);
                    renderPuzzle(state->screen, &puzzles[*currentPuzzle]);
                    if (isCorrect) {
                        renderSuccess(state->screen, victoryImage);
                    } else {
                        renderFailure(state->screen, defeatImage);
                    }
                    SDL_Flip(state->screen);
                    SDL_Delay(16);
                }
                freePuzzle(&puzzles[*currentPuzzle]);
                (*currentPuzzle)++;
                if (*currentPuzzle < TOTAL_PUZZLES) {
                    *startTime = 0; // Réinitialiser pour forcer renderEnigme à le définir
                    printf("Prochain puzzle: currentPuzzle=%d\n", *currentPuzzle);
                } else {
                    state->mode = MODE_JEU;
                    printf("Retour au mode jeu: tous les puzzles terminés\n");
                }
            } else {
                printf("Drop hors zone\n");
            }
        }
    }
}

void renderEnigme(GameState *state, Puzzle puzzles[], int currentPuzzle, DragState drag, Uint32 *startTime, Uint32 maxTime, SDL_Surface *background, SDL_Surface *victoryImage, SDL_Surface *defeatImage, Personne *perso, Personne *perso2, SDL_Surface *map) {
    if (!state || !state->screen || !background || !puzzles || !victoryImage || !defeatImage || !startTime || !perso || !perso2 || !map) {
        printf("Erreur: Arguments nuls dans renderEnigme\n");
        return;
    }

    // Réinitialiser startTime au premier rendu du puzzle
    static int lastPuzzle = -1;
    if (lastPuzzle != currentPuzzle || *startTime == 0) {
        *startTime = SDL_GetTicks();
        lastPuzzle = currentPuzzle;
        printf("startTime réinitialisé pour puzzle %d: startTime=%u\n", currentPuzzle, *startTime);
    }

    printf("renderEnigme: currentPuzzle=%d, screen: w=%d, h=%d, startTime=%u, maxTime=%u\n", currentPuzzle, state->screen->w, state->screen->h, *startTime, maxTime);

    // Ne pas rendre le background pour voir le mode joueur en dessous
    // SDL_BlitSurface(background, NULL, state->screen, NULL); // Commenté pour éviter d'effacer l'arrière-plan

    if (currentPuzzle < TOTAL_PUZZLES) {
        renderPuzzle(state->screen, &puzzles[currentPuzzle]);
        renderTimer(state->screen, *startTime, maxTime);
        Uint32 currentTicks = SDL_GetTicks();
        Uint32 elapsedTime = currentTicks - *startTime;
        printf("Vérification timeout: currentTicks=%u, startTime=%u, elapsedTime=%u, maxTime=%u\n", currentTicks, *startTime, elapsedTime, maxTime);
        if (elapsedTime >= maxTime) {
            printf("Timeout détecté après %u ms\n", elapsedTime);
            Uint32 animStart = SDL_GetTicks();
            while (SDL_GetTicks() - animStart < 1500) {
                // Rendre le mode joueur en arrière-plan
                renderJoueur(state, perso, perso2, map);
                renderPuzzle(state->screen, &puzzles[currentPuzzle]);
                renderFailure(state->screen, defeatImage);
                SDL_Flip(state->screen);
                SDL_Delay(16);
            }
            freePuzzle(&puzzles[currentPuzzle]);
            currentPuzzle++;
            if (currentPuzzle < TOTAL_PUZZLES) {
                *startTime = 0; // Forcer la réinitialisation au prochain rendu
                printf("Prochain puzzle après timeout: currentPuzzle=%d\n", currentPuzzle);
            } else {
                state->mode = MODE_JEU;
                printf("Retour au mode jeu: timeout, tous les puzzles terminés\n");
            }
        }
    } else {
        SDL_Rect message = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 25, 200, 50};
        SDL_FillRect(state->screen, &message, SDL_MapRGB(state->screen->format, 255, 255, 255));
        printf("Affichage message de fin: tous les puzzles terminés\n");
    }
}

void cleanupEnigme(Puzzle puzzles[], SDL_Surface *background, SDL_Surface *victoryImage, SDL_Surface *defeatImage) {
    if (background) SDL_FreeSurface(background);
    if (victoryImage) SDL_FreeSurface(victoryImage);
    if (defeatImage) SDL_FreeSurface(defeatImage);
    for (int i = 0; i < TOTAL_PUZZLES; i++) {
        freePuzzle(&puzzles[i]);
    }
    printf("Ressources énigme libérées\n");
}

void initPuzzle(Puzzle *p, int index) {
    if (!p) {
        printf("Erreur: Puzzle nul dans initPuzzle\n");
        return;
    }
    char path[100];
    p->played = 0;
    sprintf(path, "assets/puzzle%d/base.png", index);
    p->baseImage = IMG_Load(path);
    if (!p->baseImage) {
        printf("Erreur: Impossible de charger %s: %s\n", path, IMG_GetError());
        p->baseImage = SDL_CreateRGBSurface(SDL_SWSURFACE, 300, 300, 32, 0, 0, 0, 0);
        SDL_FillRect(p->baseImage, NULL, SDL_MapRGB(p->baseImage->format, 255, 255, 255));
    }
    sprintf(path, "assets/puzzle%d/shadow.png", index);
    p->shadowImage = IMG_Load(path);
    if (!p->shadowImage) {
        printf("Erreur: Impossible de charger %s: %s\n", path, IMG_GetError());
        p->shadowImage = SDL_CreateRGBSurface(SDL_SWSURFACE, 100, 100, 32, 0, 0, 0, 0);
        SDL_FillRect(p->shadowImage, NULL, SDL_MapRGB(p->shadowImage->format, 128, 128, 128));
        if (p->baseImage) {
            SDL_FreeSurface(p->baseImage);
            p->baseImage = NULL;
        }
        return;
    }
    SDL_Rect shadowRect;
    SDL_GetClipRect(p->shadowImage, &shadowRect);

    if (index == 1) {
        p->dropZone.x = 318;
        p->dropZone.y = 278;
    } else if (index == 2) {
        p->dropZone.x = 335;
        p->dropZone.y = 420;
    } else if (index == 3) {
        p->dropZone.x = 507;
        p->dropZone.y = 335;
    } else if (index == 4) {
        p->dropZone.x = 305;
        p->dropZone.y = 335;
    } else {
        p->dropZone.x = 353;
        p->dropZone.y = 190;
    }
    p->dropZone.w = shadowRect.w;
    p->dropZone.h = shadowRect.h;
    printf("DropZone: x=%d, y=%d, w=%d, h=%d\n", p->dropZone.x, p->dropZone.y, p->dropZone.w, p->dropZone.h);

    for (int i = 0; i < TOTAL_CHOICES; i++) {
        sprintf(path, "assets/puzzle%d/choice%d.png", index, i);
        p->choices[i] = IMG_Load(path);
        if (!p->choices[i]) {
            printf("Erreur: Impossible de charger %s: %s\n", path, IMG_GetError());
            p->choices[i] = SDL_CreateRGBSurface(SDL_SWSURFACE, 100, 100, 32, 0, 0, 0, 0);
            SDL_FillRect(p->choices[i], NULL, SDL_MapRGB(p->choices[i]->format, 0, 0, 255));
            if (p->baseImage) {
                SDL_FreeSurface(p->baseImage);
                p->baseImage = NULL;
            }
            if (p->shadowImage) {
                SDL_FreeSurface(p->shadowImage);
                p->shadowImage = NULL;
            }
            for (int j = 0; j < i; j++) {
                SDL_FreeSurface(p->choices[j]);
                p->choices[j] = NULL;
            }
            return;
        }
        if (index == 2) {
            switch (i) {
                case 0: p->choicePositions[i].x = 45; p->choicePositions[i].y = 50; break;
                case 1: p->choicePositions[i].x = 45; p->choicePositions[i].y = 180; break;
                case 2: p->choicePositions[i].x = 45; p->choicePositions[i].y = 270; break;
                default: p->choicePositions[i].x = 100 + i * 200; p->choicePositions[i].y = 420;
            }
        } else {
            p->choicePositions[i].x = 100 + i * 200;
            p->choicePositions[i].y = 420;
        }
        printf("Choix %d: x=%d, y=%d, w=%d, h=%d\n", i, p->choicePositions[i].x, p->choicePositions[i].y, p->choices[i]->w, p->choices[i]->h);
    }
    p->correctIndex = 0;
    printf("Puzzle %d initialisé\n", index);
}

void renderPuzzle(SDL_Surface *screen, Puzzle *p) {
    if (!screen || !p || !p->baseImage || !p->shadowImage) {
        printf("Erreur: Arguments nuls ou surfaces manquantes dans renderPuzzle\n");
        return;
    }
    SDL_Rect basePos = {150, 80, 0, 0};
    SDL_BlitSurface(p->baseImage, NULL, screen, &basePos);
    SDL_BlitSurface(p->shadowImage, NULL, screen, &p->dropZone);
    for (int i = 0; i < TOTAL_CHOICES; i++) {
        if (p->choices[i]) {
            SDL_BlitSurface(p->choices[i], NULL, screen, &p->choicePositions[i]);
        } else {
            printf("Erreur: Choix %d manquant dans renderPuzzle\n", i);
        }
    }
    printf("Puzzle rendu\n");
}

void renderTimer(SDL_Surface *screen, Uint32 startTime, Uint32 maxTime) {
    if (!screen) {
        printf("Erreur: Écran nul dans renderTimer\n");
        return;
    }
    Uint32 now = SDL_GetTicks();
    float progress = 1.0f - (float)(now - startTime) / maxTime;
    if (progress < 0) progress = 0;
    int barWidth = SCREEN_WIDTH * progress;
    SDL_Rect bar = {0, 20, barWidth, 20};
    SDL_FillRect(screen, &bar, SDL_MapRGB(screen->format, 255, 153, 0));
    printf("Timer rendu: startTime=%u, now=%u, progress=%f, barWidth=%d\n", startTime, now, progress, barWidth);
}

int checkDrop(Puzzle *p, int x, int y) {
    if (!p) {
        printf("Erreur: Puzzle nul dans checkDrop\n");
        return 0;
    }
    int inZone = (x >= p->dropZone.x && x <= p->dropZone.x + p->dropZone.w &&
                  y >= p->dropZone.y && y <= p->dropZone.y + p->dropZone.h);
    printf("CheckDrop: x=%d, y=%d, dropZone(x=%d, y=%d, w=%d, h=%d), inZone=%d\n", 
           x, y, p->dropZone.x, p->dropZone.y, p->dropZone.w, p->dropZone.h, inZone);
    return inZone;
}

void renderSuccess(SDL_Surface *screen, SDL_Surface *victoryImage) {
    if (!screen || !victoryImage) {
        printf("Erreur: Arguments nuls dans renderSuccess\n");
        return;
    }
    float zoom = 1.0f + 0.2f * sin(SDL_GetTicks() * 0.01f);
    SDL_Surface *zoomed = rotozoomSurface(victoryImage, 0, zoom, 1);
    if (zoomed) {
        SDL_Rect dstrect = {(screen->w - zoomed->w) / 2, (screen->h - zoomed->h) / 2, 0, 0};
        boxRGBA(screen, 0, 0, screen->w, screen->h, 0, 0, 0, 128);
        SDL_BlitSurface(zoomed, NULL, screen, &dstrect);
        SDL_FreeSurface(zoomed);
        printf("Succès rendu\n");
    } else {
        printf("Erreur: Échec de la création de la surface zoomée dans renderSuccess\n");
    }
}

void renderFailure(SDL_Surface *screen, SDL_Surface *defeatImage) {
    if (!screen || !defeatImage) {
        printf("Erreur: Arguments nuls dans renderFailure\n");
        SDL_Rect rect = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100};
        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 150, 0, 0));
        stringColor(screen, SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 - 10, "ECHEC!", SDL_MapRGB(screen->format, 255, 255, 255));
        return;
    }
    int shake_x = (rand() % 20) - 10;
    int shake_y = (rand() % 20) - 10;
    SDL_Rect dstrect = {(screen->w - defeatImage->w) / 2 + shake_x, (screen->h - defeatImage->h) / 2 + shake_y, 0, 0};
    SDL_Surface *overlay = SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    if (overlay) {
        SDL_FillRect(overlay, NULL, SDL_MapRGBA(overlay->format, 100, 0, 0, 128));
        SDL_BlitSurface(overlay, NULL, screen, NULL);
        SDL_FreeSurface(overlay);
        printf("Échec rendu\n");
    } else {
        printf("Erreur: Échec de la création de l'overlay dans renderFailure\n");
    }
    SDL_BlitSurface(defeatImage, NULL, screen, &dstrect);
}

void freePuzzle(Puzzle *p) {
    if (!p) {
        printf("Erreur: Puzzle nul dans freePuzzle\n");
        return;
    }
    if (p->baseImage) {
        SDL_FreeSurface(p->baseImage);
        p->baseImage = NULL;
    }
    if (p->shadowImage) {
        SDL_FreeSurface(p->shadowImage);
        p->shadowImage = NULL;
    }
    for (int i = 0; i < TOTAL_CHOICES; i++) {
        if (p->choices[i]) {
            SDL_FreeSurface(p->choices[i]);
            p->choices[i] = NULL;
        }
    }
    printf("Puzzle libéré\n");
}
