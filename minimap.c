#include "minimap.h"
#include <stdlib.h>

void initMinimap(Minimap *m, int width, int height, int scaling, int pos_x, int pos_y) {
    m->scaling_factor = scaling;
    m->position = (SDL_Rect){pos_x, pos_y, width * scaling / 100, height * scaling / 100};
   
    // Create minimap surface
    m->mini_bg = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                     m->position.w,
                                     m->position.h,
                                     32,
                                     0, 0, 0, 0);
   
    // Set colors
    m->player_color = SDL_MapRGB(m->mini_bg->format, 255, 0, 0);
    m->platform_color = SDL_MapRGB(m->mini_bg->format, 100, 100, 100);
    m->movable_color = SDL_MapRGB(m->mini_bg->format, 200, 100, 100);
    m->destructible_color = SDL_MapRGB(m->mini_bg->format, 100, 200, 100);
}

void updateMinimap(Minimap *m, GameState *game) {
    // Clear minimap
    SDL_FillRect(m->mini_bg, NULL, SDL_MapRGB(m->mini_bg->format, 50, 50, 80));
   
    // Draw platforms
    for (int i = 0; i < game->platform_count; i++) {
        if (game->platforms[i].is_active) {
            SDL_Rect platform_rect = {
                game->platforms[i].rect.x * m->scaling_factor / 100,
                game->platforms[i].rect.y * m->scaling_factor / 100,
                game->platforms[i].rect.w * m->scaling_factor / 100,
                game->platforms[i].rect.h * m->scaling_factor / 100
            };
           
            Uint32 color = m->platform_color;
            if (game->platforms[i].is_movable) color = m->movable_color;
            if (i == 4) color = m->destructible_color; // Example destructible
           
            SDL_FillRect(m->mini_bg, &platform_rect, color);
        }
    }
   
    // Draw player
    SDL_Rect player_rect = {
        game->player.rect.x * m->scaling_factor / 100,
        game->player.rect.y * m->scaling_factor / 100,
        4, 4  // Small dot for player
    };
    SDL_FillRect(m->mini_bg, &player_rect, m->player_color);
}

void drawMinimap(SDL_Surface *screen, Minimap *m) {
    // Draw minimap border
    SDL_Rect border = {m->position.x-2, m->position.y-2, m->position.w+4, m->position.h+4};
    SDL_FillRect(screen, &border, SDL_MapRGB(screen->format, 255, 255, 255));
   
    // Draw minimap
    SDL_BlitSurface(m->mini_bg, NULL, screen, &m->position);
}

void freeMinimap(Minimap *m) {
    SDL_FreeSurface(m->mini_bg);
}



