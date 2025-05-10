#include "joueur.h"

void initMinimap(Minimap *m, int width, int height, int scaling, int pos_x, int pos_y, SDL_Surface *map) {
    if (!m || !map) return;
    m->mini_bg = SDL_CreateRGBSurface(SDL_SWSURFACE, MINIMAP_WIDTH, MINIMAP_HEIGHT, 32, 0, 0, 0, 0);
    if (!m->mini_bg) {
        printf("Erreur: Impossible de créer la surface de la minimap\n");
        return;
    }
    SDL_BlitSurface(map, NULL, m->mini_bg, &(SDL_Rect){0, 0, MINIMAP_WIDTH, MINIMAP_HEIGHT});
    m->position.x = pos_x;
    m->position.y = pos_y;
    m->position.w = MINIMAP_WIDTH;
    m->position.h = MINIMAP_HEIGHT;
    m->scaling_factor = scaling;
    m->player1_color = SDL_MapRGB(m->mini_bg->format, 255, 0, 0);
    m->player2_color = SDL_MapRGB(m->mini_bg->format, 0, 0, 255);
    printf("Minimap initialisée: w=%d, h=%d, pos_x=%d, pos_y=%d\n", m->position.w, m->position.h, pos_x, pos_y);
}

void updateMinimap(Minimap *m, Personne *perso, Personne *perso2) {
    if (!m || !perso || !perso2 || !m->mini_bg) return;
    SDL_FillRect(m->mini_bg, NULL, SDL_MapRGB(m->mini_bg->format, 0, 0, 0));
    SDL_BlitSurface(m->mini_bg, NULL, m->mini_bg, NULL);
    int x1 = perso->pos_hero.x / m->scaling_factor;
    int y1 = perso->pos_hero.y / m->scaling_factor;
    int x2 = perso2->pos_hero.x / m->scaling_factor;
    int y2 = perso2->pos_hero.y / m->scaling_factor;
    SDL_Rect rect1 = {x1, y1, 5, 5};
    SDL_Rect rect2 = {x2, y2, 5, 5};
    SDL_FillRect(m->mini_bg, &rect1, m->player1_color);
    SDL_FillRect(m->mini_bg, &rect2, m->player2_color);
    printf("Minimap mise à jour: Perso1 (%d,%d), Perso2 (%d,%d)\n", x1, y1, x2, y2);
}

void drawMinimap(SDL_Surface *screen, Minimap *m) {
    if (!screen || !m || !m->mini_bg) return;
    SDL_BlitSurface(m->mini_bg, NULL, screen, &m->position);
    printf("Minimap dessinée à x=%d, y=%d\n", m->position.x, m->position.y);
}

void freeMinimap(Minimap *m) {
    if (!m) return;
    if (m->mini_bg) {
        printf("Libération de la surface de la minimap\n");
        SDL_FreeSurface(m->mini_bg);
        m->mini_bg = NULL;
    }
}
