#ifndef DOMINOS_TYPES_H
#define DOMINOS_TYPES_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../game.h"

#define MAX_PLACEMENT_LOCATIONS 8
#define DOMINO_WIDTH 30
#define DOMINO_HEIGHT 60
#define PADDING 5

typedef struct {
    int left;
    int right;
    bool left_available;
    bool right_available;
    SDL_Rect rect;
    bool visible;
    bool placed;
    bool selected;
    int rotation_angle; 
} Domino;


typedef struct PlacedDomino{       
   Domino domino;  
   bool vertical;   
} PlacedDomino;

typedef struct {
   SDL_Rect rect;
   SDL_Rect yes_button;
   SDL_Rect no_button;
   bool is_visible;
} QuitDialogt;

typedef struct {
    SDL_Rect location;
    bool is_valid;
} PlacementLocation;

typedef struct {
   Domino* player_hand;
   bool plateau_vide;
   Domino* opponent_hand;
   int ordre_joueurs[4];
   char noms_joueurs[4][20];
   int score[4];
   int nbr_joueurs;
   Domino* deck;
   int deck_size;
   int hand_size;
   int board_size;
   int current_player;
   bool game_started;
   QuitDialogt quit_dialog;
   SDL_Rect playing_area;
   PlacedDomino placed_dominos[28];
   int placed_dominos_count;
   int max_placed_dominos;
   PlacementLocation placement_locations[MAX_PLACEMENT_LOCATIONS];
    int placement_location_count;
} DominosGame;

#endif