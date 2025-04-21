#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "enigme.h"

// Initialisation des surfaces et polices pour le quiz
void init_enigme(enigme *en) {
    srand(time(NULL)); // Initialisation du random pour mélanger les questions

    en->image_enigme = IMG_Load("quiz_bg.jpg");
    en->position_enigme.x = 0;
    en->position_enigme.y = 0;

    en->correct = IMG_Load("correct.png");
    en->wrong = IMG_Load("wrong.png");
    en->position_correct.x = 300;
    en->position_correct.y = 200;
    en->position_wrong.x = 300;
    en->position_wrong.y = 200;

    TTF_Init();
    en->police = TTF_OpenFont("arial.ttf", 24);
    en->police_q = TTF_OpenFont("arial.ttf", 28);
    en->police_timer = TTF_OpenFont("arial.ttf", 20);

    en->pos_question.x = 100;
    en->pos_question.y = 100;
    en->pos_reponse_1.x = 150;
    en->pos_reponse_1.y = 250;
    en->pos_reponse_2.x = 150;
    en->pos_reponse_2.y = 320;
    en->pos_reponse_3.x = 150;
    en->pos_reponse_3.y = 390;

    en->pos_timer.x = 600;
    en->pos_timer.y = 50;

    en->current_question = 0;
    en->score = 0;

    load_questions(en);  // Charger les questions et mélanger
}

// Mélange les questions de manière aléatoire
void shuffle_questions(question *q_array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        question temp = q_array[i];
        q_array[i] = q_array[j];
        q_array[j] = temp;
    }
}

// Chargement des questions depuis un fichier texte
void load_questions(enigme *en) {
    FILE* file = fopen("question.text", "r");
    if (!file) {
        printf("Erreur : impossible d'ouvrir le fichier de questions\n");
        return;
    }

    char line[512];
    int count = 0;

    // Lire toutes les questions et les réponses
    while (fgets(line, sizeof(line), file) && count < MAX_QUESTIONS) {
        char* q = strtok(line, "?");
        char* a = strtok(NULL, " ");
        char* b = strtok(NULL, " ");
        char* c = strtok(NULL, "\n");

        if (q && a && b && c) {
            snprintf(en->questions[count].question, MAX_QUESTION_LENGTH, "%s?", q);
            strncpy(en->questions[count].answers[0], a, MAX_ANSWER_LENGTH - 1);
            strncpy(en->questions[count].answers[1], b, MAX_ANSWER_LENGTH - 1);
            strncpy(en->questions[count].answers[2], c, MAX_ANSWER_LENGTH - 1);
            en->questions[count].correct_answer = rand() % 3;  // Randomiser la bonne réponse parmi les 3 choix
            count++;
        }
    }

    fclose(file);
    en->question_count = count;
    en->total_questions = count;

    shuffle_questions(en->questions, count); // Mélanger les questions
}

// Affichage du texte centré
SDL_Surface* afficher_texte_centre(const char *texte, TTF_Font *police, SDL_Color couleur) {
    return TTF_RenderText_Blended(police, texte, couleur);
}

// Affichage du quiz SDL
void quiz1(enigme *en, SDL_Surface *screen) {
    if (en->current_question >= en->total_questions) return;

    SDL_Event event;
    int done = 0;
    int answer_selected = -1;
    SDL_Color white = {255, 255, 255};
    SDL_Color red = {255, 0, 0};

    question* q = &en->questions[en->current_question];

    en->question = TTF_RenderText_Blended(en->police_q, q->question, white);
    en->reponse_1 = TTF_RenderText_Blended(en->police, q->answers[0], white);
    en->reponse_2 = TTF_RenderText_Blended(en->police, q->answers[1], white);
    en->reponse_3 = TTF_RenderText_Blended(en->police, q->answers[2], white);

    en->question_start_time = SDL_GetTicks();

    while (!done) {
        SDL_BlitSurface(en->image_enigme, NULL, screen, &en->position_enigme);
        SDL_BlitSurface(en->question, NULL, screen, &en->pos_question);
        SDL_BlitSurface(en->reponse_1, NULL, screen, &en->pos_reponse_1);
        SDL_BlitSurface(en->reponse_2, NULL, screen, &en->pos_reponse_2);
        SDL_BlitSurface(en->reponse_3, NULL, screen, &en->pos_reponse_3);

        Uint32 time_elapsed = SDL_GetTicks() - en->question_start_time;
        Uint32 time_remaining = (time_elapsed > QUESTION_TIME) ? 0 : (QUESTION_TIME - time_elapsed);

        char time_text[32];
        sprintf(time_text, "Temps restant : %d sec", time_remaining / 1000);
        en->timer_text = TTF_RenderText_Blended(en->police_timer, time_text, red);
        SDL_BlitSurface(en->timer_text, NULL, screen, &en->pos_timer);

        SDL_Flip(screen);

        if (time_remaining == 0) {
            SDL_BlitSurface(en->wrong, NULL, screen, &en->position_wrong);
            SDL_Flip(screen);
            SDL_Delay(1000);
            done = 1;
            continue;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = 1;
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x;
                int y = event.button.y;

                if (x >= en->pos_reponse_1.x && x <= en->pos_reponse_1.x + 400 &&
                    y >= en->pos_reponse_1.y && y <= en->pos_reponse_1.y + 40)
                    answer_selected = 0;
                else if (x >= en->pos_reponse_2.x && x <= en->pos_reponse_2.x + 400 &&
                         y >= en->pos_reponse_2.y && y <= en->pos_reponse_2.y + 40)
                    answer_selected = 1;
                else if (x >= en->pos_reponse_3.x && x <= en->pos_reponse_3.x + 400 &&
                         y >= en->pos_reponse_3.y && y <= en->pos_reponse_3.y + 40)
                    answer_selected = 2;
            }
        }

        if (answer_selected != -1) {
            if (answer_selected == q->correct_answer) {
                SDL_BlitSurface(en->correct, NULL, screen, &en->position_correct);
                en->score++;
            } else {
                SDL_BlitSurface(en->wrong, NULL, screen, &en->position_wrong);
            }
            SDL_Flip(screen);
            SDL_Delay(1000);
            done = 1;
        }
    }

    en->current_question++;
}

