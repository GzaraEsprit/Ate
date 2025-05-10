#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "joueur.h"
#include "enigme.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL init failed: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0) {
        printf("TTF init failed: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Mixer init failed: %s\n", Mix_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if (!screen) {
        printf("Failed to set video mode %dx%d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    GameState state = {0};
    state.screen = screen;
    state.quitter = 0;
    state.mode = MODE_JEU;

    Personne perso = {0}, perso2 = {0};
    initPerso(&perso);
    initPerso2(&perso2);

    SDL_Surface *map = IMG_Load("image/map.png");
    if (!map) {
        printf("Erreur: Impossible de charger image/map.png: %s\n", IMG_GetError());
        free_perso(&perso);
        free_perso(&perso2);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    initMinimap(&state.minimap, MINIMAP_WIDTH, MINIMAP_HEIGHT, 15, SCREEN_WIDTH - 210, 10, map);

    Mix_Music *musique = Mix_LoadMUS("audio/music.mp3");
    if (musique) Mix_PlayMusic(musique, -1);
    Mix_Chunk *attack = Mix_LoadWAV("audio/attack.wav");

    // Initialisation des ressources pour le mode énigme
    Puzzle puzzles[TOTAL_PUZZLES];
    DragState drag = {0};
    SDL_Surface *background = NULL;
    SDL_Surface *victoryImage = NULL;
    SDL_Surface *defeatImage = NULL;

    // Initialisation des puzzles et des images
    initEnigme(puzzles, &background, &victoryImage, &defeatImage);
    if (!background || !victoryImage || !defeatImage) {
        printf("Erreur: Une ou plusieurs ressources pour le mode énigme n'ont pas pu être initialisées.\n");
        cleanupJoueur(&state, &perso, &perso2, musique, attack, map);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    Uint32 startTime = SDL_GetTicks();
    Uint32 maxTime = 30000; // 30 secondes
    int currentPuzzle = 0;

    // Charger les ressources pour les énigmes
    loadResourcesEnigme(puzzles, &currentPuzzle, &startTime);

    int running = 1;
    Uint32 lastTime = SDL_GetTicks();
    while (running) {
        printf("Boucle principale: running=%d, quitter=%d, mode=%d\n", running, state.quitter, state.mode);
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // Gérer les événements en fonction du mode
        if (state.mode == MODE_JEU) {
            handleEventsJoueur(&state, &perso, &perso2, attack);
        } else if (state.mode == MODE_ENIGME) {
            handleEventsEnigme(&state, puzzles, &currentPuzzle, &drag, &startTime, maxTime, victoryImage, defeatImage, &perso, &perso2, map);
        }

        // Mettre à jour le mode joueur
        updateJoueur(&perso, &perso2, deltaTime);

        // Toujours rendre le mode joueur en arrière-plan
        renderJoueur(&state, &perso, &perso2, map);

        // Si on est en mode énigme, rendre l'interface énigme par-dessus
        if (state.mode == MODE_ENIGME) {
            renderEnigme(&state, puzzles, currentPuzzle, drag, &startTime, maxTime, background, victoryImage, defeatImage, &perso, &perso2, map);
        }

        if (state.quitter) {
            printf("Sortie demandée: state.quitter=%d\n", state.quitter);
            running = 0;
        }

        SDL_Flip(state.screen);
        SDL_Delay(16);
    }

    printf("Fin de la boucle principale\n");
    cleanupJoueur(&state, &perso, &perso2, musique, attack, map);
    cleanupEnigme(puzzles, background, victoryImage, defeatImage);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    printf("Programme terminé\n");
    return 0;
}
