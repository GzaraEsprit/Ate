#ifndef JOUEUR_H
#define JOUEUR_H

#include "common.h"

void initPerso(Personne *p);
void initPerso2(Personne *p2);
void handleEventsJoueur(GameState *state, Personne *perso, Personne *perso2, Mix_Chunk *attack);
void updateJoueur(Personne *perso, Personne *perso2, float deltaTime);
void renderJoueur(GameState *state, Personne *perso, Personne *perso2, SDL_Surface *map);
void cleanupJoueur(GameState *state, Personne *perso, Personne *perso2, Mix_Music *musique, Mix_Chunk *attack, SDL_Surface *map);
void animerPerso(Personne *p);
void deplacerPerso(Personne *p, float deltaTime);
void saut(Personne *p, float deltaTime);
void gravity(Personne *p, float deltaTime);
void afficherPerso(Personne p, SDL_Surface *screen_p);
void afficherScore_vie(Personne p, SDL_Surface *screen_s);
void free_perso(Personne *p);
void initMinimap(Minimap *m, int width, int height, int scaling, int pos_x, int pos_y, SDL_Surface *map);
void updateMinimap(Minimap *m, Personne *perso, Personne *perso2);
void drawMinimap(SDL_Surface *screen, Minimap *m);
void freeMinimap(Minimap *m);

#endif
