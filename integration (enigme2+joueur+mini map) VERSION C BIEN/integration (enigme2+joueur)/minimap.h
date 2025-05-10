#ifndef MINIMAP_H
#define MINIMAP_H

#include "common.h"

void initMinimap(Minimap *m, int width, int height, int scaling, int pos_x, int pos_y, SDL_Surface *map);
void updateMinimap(Minimap *m, Personne *perso, Personne *perso2);
void drawMinimap(SDL_Surface *screen, Minimap *m);
void freeMinimap(Minimap *m);

#endif
