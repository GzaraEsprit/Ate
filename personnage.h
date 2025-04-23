#ifndef PERSONNAGE_DEF
#define PERSONNAGE_DEF
// INCLUDES :
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include <SDL/SDL_ttf.h>

//STRUCT : 
typedef enum STATE STATE;
enum STATE {WAITING,WALKING,JUMP,DOUBLEJUMP,DUCK,ATTACKING,ATTACKING2,HIT,DIE};

typedef struct
{
	SDL_Surface *hero_d;
	SDL_Surface *hero_g;
	SDL_Surface *bar_score;
	SDL_Surface *bar_health;
	SDL_Rect pos_hero,pos_vie,pos_score;
	int direction,health,score,death,vitesse,jump,jump_count;
	double acceleration;
	SDL_Rect annimation_hero_d[9][20];
	SDL_Rect annimation_hero_g[9][20];
	int frame_w,frame_wl,frame_j,frame_dj,frame_du,frame_a,frame_a2,frame_h,frame_d;
	STATE state;
	TTF_Font *police;
}Personne;

//FUNCTIONS :
void initPerso2(Personne *p);
void initPerso(Personne *p);
void deplacerPerso (Personne *p);
void animerPerso (Personne* p);
void saut (Personne* p);
void gravity(Personne* p);
void afficherPerso(Personne p, SDL_Surface * screen_p);
void afficherScore_vie(Personne p, SDL_Surface * screen_s);
void free_perso(Personne *p);
#endif
