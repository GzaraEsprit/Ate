#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h> // ✅ Nécessaire pour srand(time(NULL))
#include "enigme.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    // ✅ Initialisation du générateur de nombres aléatoires UNE SEULE FOIS
    srand(time(NULL));

    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Self-Discovery Quiz", NULL);

    enigme en;
    init_enigme(&en);        // Chargement des images, sons, etc.
    load_questions(&en);     // Lecture et mélange des questions (après srand !)
    
    animation(screen);       // Affiche une animation d’intro (si elle existe)

    int running = 1;
    while (running) {
        int result = quiz1(&en, screen);  // Lancement du quiz
        
        if (result == -1) {
            running = 0; // L'utilisateur a quitté
        }
        else if (result == 0) {
            display_results(&en, screen); // Affiche les résultats
            running = 0;
        }

        free_surface_enigme(&en); // Libération des surfaces SDL (images/sons)
    }

    // Par précaution, on libère une dernière fois
    free_surface_enigme(&en);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

