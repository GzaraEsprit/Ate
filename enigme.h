#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define MAX_QUESTIONS 10
#define MAX_QUESTION_LENGTH 256
#define MAX_ANSWER_LENGTH 100
#define QUESTION_TIME 30000 // 30 seconds in milliseconds

typedef struct {
    char question[MAX_QUESTION_LENGTH];
    char answers[3][MAX_ANSWER_LENGTH];
    int correct_answer;
} Question;

struct enigme {
    SDL_Surface* image_enigme;
    SDL_Rect position_enigme;
    
    SDL_Surface *correct, *wrong;
    SDL_Rect position_correct, position_wrong;
    
    TTF_Font *police, *police_q, *police_timer;
    SDL_Surface *reponse_1, *reponse_2, *reponse_3, *question, *timer_text;
    SDL_Rect pos_reponse_1, pos_reponse_2, pos_reponse_3, pos_question, pos_timer;
    
    Question questions[MAX_QUESTIONS];
    int current_question;
    int total_questions;
    int score;
    Uint32 question_start_time;
};

typedef struct enigme enigme;

void init_enigme(enigme* en);
void load_questions(enigme *en);
void blit_enigme(enigme *en, SDL_Surface* screen);
void free_surface_enigme(enigme *en);
int quiz1(enigme *en, SDL_Surface* screen);
void display_results(enigme *en, SDL_Surface* screen);
void animation(SDL_Surface *screen);
void update_timer(enigme *en, SDL_Surface *screen);

#endif // ENIGME_H_INCLUDED
