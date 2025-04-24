#include "game.h"
#include <stdlib.h>
#include <stdbool.h>

#define GRAVITY 1
#define JUMP_FORCE -15
#define MOVE_SPEED 5

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

void initGame(GameState *game) {
    // Initialize player
    game->player.rect = (SDL_Rect){100, 100, 30, 50};
    game->player.color = (SDL_Color){255, 0, 0, 255};
    game->player.vel_x = 0;
    game->player.vel_y = 0;
    game->player.is_grounded = 0;

    // Initialize platforms
    game->platform_count = 5;
    game->platforms = malloc(sizeof(Platform) * game->platform_count);
   
    // Ground (make sure it's at the bottom of the screen)
    game->platforms[0] = (Platform){(SDL_Rect){0, 550, 800, 50}, (SDL_Color){100, 100, 100, 255}, 0, 1};
   
    // Platforms
    game->platforms[1] = (Platform){(SDL_Rect){100, 450, 200, 20}, (SDL_Color){150, 150, 150, 255}, 0, 1};
    game->platforms[2] = (Platform){(SDL_Rect){400, 350, 150, 20}, (SDL_Color){150, 150, 150, 255}, 0, 1};
   
    // Movable platform
    game->platforms[3] = (Platform){(SDL_Rect){300, 250, 100, 20}, (SDL_Color){200, 100, 100, 255}, 1, 1};
   
    // Destructible platform
    game->platforms[4] = (Platform){(SDL_Rect){600, 380, 100, 20}, (SDL_Color){100, 200, 100, 255}, 0, 1};

    // Initialize camera
    game->camera = (SDL_Rect){0, 0, 800, 600};
}

void handleInput(GameState *game) {
    const Uint8 *keys = SDL_GetKeyState(NULL);
   
    game->player.vel_x = 0; // Reset horizontal velocity
   
    if (keys[SDLK_LEFT]) {
        game->player.vel_x = -MOVE_SPEED;
    }
    if (keys[SDLK_RIGHT]) {
        game->player.vel_x = MOVE_SPEED;
    }
    if (keys[SDLK_SPACE] && game->player.is_grounded) {
        game->player.vel_y = JUMP_FORCE;
        game->player.is_grounded = 0;
    }
}

void updateGame(GameState *game) {
    // Apply gravity if not grounded
    if (!game->player.is_grounded) {
        game->player.vel_y += GRAVITY;
    }
   
    // Update X position
    game->player.rect.x += game->player.vel_x;
   
    // Check X collisions
    for (int i = 0; i < game->platform_count; i++) {
        if (game->platforms[i].is_active && checkCollision(game->player.rect, game->platforms[i].rect)) {
            if (game->player.vel_x > 0) {
                game->player.rect.x = game->platforms[i].rect.x - game->player.rect.w;
            } else if (game->player.vel_x < 0) {
                game->player.rect.x = game->platforms[i].rect.x + game->platforms[i].rect.w;
            }
        }
    }
   
    // Update Y position
    game->player.rect.y += game->player.vel_y;
    game->player.is_grounded = 0;
   
    // Check Y collisions
    for (int i = 0; i < game->platform_count; i++) {
        if (game->platforms[i].is_active && checkCollision(game->player.rect, game->platforms[i].rect)) {
            // Check if hitting destructible platform from below
            if (i == 4 && game->player.vel_y < 0) {
                game->platforms[i].is_active = 0;
                continue;
            }
           
            if (game->player.vel_y > 0) {
                game->player.rect.y = game->platforms[i].rect.y - game->player.rect.h;
                game->player.is_grounded = 1;
                game->player.vel_y = 0;
            } else if (game->player.vel_y < 0) {
                game->player.rect.y = game->platforms[i].rect.y + game->platforms[i].rect.h;
                game->player.vel_y = 0;
            }
        }
    }
   
    // Update movable platform
    if (game->platforms[3].is_active) {
        game->platforms[3].rect.x += 1;
        if (game->platforms[3].rect.x > 500) game->platforms[3].rect.x = 200;
    }
   
    // Update camera
    game->camera.x = game->player.rect.x - 400;
    if (game->camera.x < 0) game->camera.x = 0;
    if (game->camera.x > 1600 - 800) game->camera.x = 1600 - 800;
}

void renderGame(SDL_Surface *screen, GameState *game) {
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
   
    // Draw platforms
    for (int i = 0; i < game->platform_count; i++) {
        if (game->platforms[i].is_active) {
            SDL_Rect platform_rect = game->platforms[i].rect;
            platform_rect.x -= game->camera.x;
            platform_rect.y -= game->camera.y;
            SDL_FillRect(screen, &platform_rect,
                        SDL_MapRGB(screen->format,
                                  game->platforms[i].color.r,
                                  game->platforms[i].color.g,
                                  game->platforms[i].color.b));
        }
    }
   
    // Draw player
    SDL_Rect player_rect = game->player.rect;
    player_rect.x -= game->camera.x;
    player_rect.y -= game->camera.y;
    SDL_FillRect(screen, &player_rect,
                SDL_MapRGB(screen->format,
                          game->player.color.r,
                          game->player.color.g,
                          game->player.color.b));
}
