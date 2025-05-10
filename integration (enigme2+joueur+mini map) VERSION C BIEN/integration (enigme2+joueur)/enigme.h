#ifndef ENIGME_H
#define ENIGME_H

#include <SDL/SDL.h>
#include "common.h"
#include "joueur.h" // Ajout pour inclure les définitions de Personne

#define TOTAL_PUZZLES 5
#define TOTAL_CHOICES 3

typedef struct {
    SDL_Surface *baseImage;
    SDL_Surface *shadowImage;
    SDL_Surface *choices[TOTAL_CHOICES];
    SDL_Rect choicePositions[TOTAL_CHOICES];
    SDL_Rect dropZone;
    int correctIndex;
    int played;
} Puzzle;

typedef struct {
    int dragging;
    int draggedIndex;
    int offsetX, offsetY;
} DragState;

void initEnigme(Puzzle puzzles[], SDL_Surface **background, SDL_Surface **victoryImage, SDL_Surface **defeatImage);
void loadResourcesEnigme(Puzzle puzzles[], int *currentPuzzle, Uint32 *startTime);
void handleEventsEnigme(GameState *state, Puzzle puzzles[], int *currentPuzzle, DragState *drag, Uint32 *startTime, Uint32 maxTime, SDL_Surface *victoryImage, SDL_Surface *defeatImage, Personne *perso, Personne *perso2, SDL_Surface *map);
void renderEnigme(GameState *state, Puzzle puzzles[], int currentPuzzle, DragState drag, Uint32 *startTime, Uint32 maxTime, SDL_Surface *background, SDL_Surface *victoryImage, SDL_Surface *defeatImage, Personne *perso, Personne *perso2, SDL_Surface *map);
void cleanupEnigme(Puzzle puzzles[], SDL_Surface *background, SDL_Surface *victoryImage, SDL_Surface *defeatImage);
void initPuzzle(Puzzle *p, int index);
void renderPuzzle(SDL_Surface *screen, Puzzle *p);
void renderTimer(SDL_Surface *screen, Uint32 startTime, Uint32 maxTime);
int checkDrop(Puzzle *p, int x, int y);
void renderSuccess(SDL_Surface *screen, SDL_Surface *victoryImage);
void renderFailure(SDL_Surface *screen, SDL_Surface *defeatImage);
void freePuzzle(Puzzle *p);

#endif
