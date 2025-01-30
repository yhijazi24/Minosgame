#ifndef TRIOMINO_TYPES_H
#define TRIOMINO_TYPES_H

#include <stdbool.h>
#include <SDL2/SDL.h>


typedef struct Triomino {
    int value1;
    int value2;
    int value3;
    bool selected;   
    bool visible;    
    SDL_Rect rect;   
    struct Triomino* suivant; 
} Triomino;

typedef struct {
   SDL_Rect rect;
   SDL_Rect yes_button;
   SDL_Rect no_button;
   bool is_visible;
} QuitDialog;

typedef struct {
    Triomino* player_hands[4]; 
    int score[4];
    int deck_size;             
    int nombreJoueurs;         
    SDL_Rect playing_area;     
    bool game_started;    
   QuitDialog quit_dialog;     
} TriominoGame;


Triomino* creer_triomino(int v1, int v2, int v3);

#endif 
