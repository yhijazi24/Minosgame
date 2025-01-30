#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "dominos_events.h"
#include "dominos_types.h"
#include "dominos_game.h"
#include "../player_setup.h"
#include "dominos_game.h"
#include "dominos_types.h"
#include "dominos_renderer.h"

#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define BUTTON_SPACING 10

void place_selected_domino_middle(DominosGame* dominos_state, Domino domino_selected) {

    dominos_state->placed_dominos[0].domino = domino_selected;
    dominos_state->placed_dominos[0].domino.rect.x = 575;
    dominos_state->placed_dominos[0].domino.rect.y = 400;
    dominos_state->placed_dominos[0].domino.selected = false;

    if (domino_selected.left == domino_selected.right) {
        dominos_state->placed_dominos[0].vertical = true;
        dominos_state->placed_dominos[0].domino.rect.w = 30;
        dominos_state->placed_dominos[0].domino.rect.h = 60;
    } else {
        dominos_state->placed_dominos[0].vertical = false; 
        dominos_state->placed_dominos[0].domino.rect.w = 60;
        dominos_state->placed_dominos[0].domino.rect.h = 30;
    }

}

void place_selected_domino_right(DominosGame* dominos_state, Domino domino_selected, int i) {
    PlacedDomino* placed = dominos_state->placed_dominos;

    placed[dominos_state->placed_dominos_count+1].domino = domino_selected;

    if(placed[i].domino.left != placed[i].domino.right){  //pas un double sur le plateau
        if (domino_selected.left == domino_selected.right) { //double à poser
            placed[dominos_state->placed_dominos_count+1].domino.rect.x = placed[i].domino.rect.x+60;
            placed[dominos_state->placed_dominos_count+1].domino.rect.y = placed[i].domino.rect.y-15 ;
            dominos_state->placed_dominos[dominos_state->placed_dominos_count+1].vertical = true;
            dominos_state->placed_dominos[dominos_state->placed_dominos_count+1].domino.rect.w = 30;                
            dominos_state->placed_dominos[dominos_state->placed_dominos_count+1].domino.rect.h = 60;
        } else { //pas un double à poser
            placed[dominos_state->placed_dominos_count+1].domino.rect.x = placed[i].domino.rect.x+60;
            placed[dominos_state->placed_dominos_count+1].domino.rect.y = placed[i].domino.rect.y ;                
            dominos_state->placed_dominos[dominos_state->placed_dominos_count+1].vertical = false;
            dominos_state->placed_dominos[dominos_state->placed_dominos_count+1].domino.rect.w = 60;
            dominos_state->placed_dominos[dominos_state->placed_dominos_count+1].domino.rect.h = 30;
        }
    } else { //double sur le plateau
        placed[dominos_state->placed_dominos_count+1].domino.rect.x = placed[i].domino.rect.x+30;
        placed[dominos_state->placed_dominos_count+1].domino.rect.y = placed[i].domino.rect.y+15 ;               
        dominos_state->placed_dominos[dominos_state->placed_dominos_count+1].vertical = false;
        dominos_state->placed_dominos[dominos_state->placed_dominos_count+1].domino.rect.w = 60;
        dominos_state->placed_dominos[dominos_state->placed_dominos_count+1].domino.rect.h = 30;

    }
    placed[i].domino.right_available = false ;   
    placed[dominos_state->placed_dominos_count+1].domino.left_available = false ;   
    dominos_state->placed_dominos_count += 1;
}




void place_selected_domino_upside_right(DominosGame* dominos_state, Domino domino_selected, int i) {
    PlacedDomino* placed = dominos_state->placed_dominos;

    placed[dominos_state->placed_dominos_count +1].domino = domino_selected;
    placed[dominos_state->placed_dominos_count +1].domino.left = domino_selected.right; //on inverse le domino
    placed[dominos_state->placed_dominos_count +1].domino.right = domino_selected.left;

    placed[dominos_state->placed_dominos_count +1].domino.rect.x = placed[i].domino.rect.x+60;
    placed[dominos_state->placed_dominos_count +1].domino.rect.y = placed[i].domino.rect.y ;                
    dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].vertical = false;
    dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].domino.rect.w = 60;
    dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].domino.rect.h = 30;

    placed[i].domino.right_available = false ;   
    placed[dominos_state->placed_dominos_count +1].domino.left_available = false ;  
    dominos_state->placed_dominos_count += 1;

}

void place_selected_domino_left(DominosGame* dominos_state, Domino domino_selected, int i) {
    PlacedDomino* placed = dominos_state->placed_dominos;

    placed[dominos_state->placed_dominos_count +1].domino = domino_selected;

    if(placed[i].domino.left != placed[i].domino.right){  //pas un double sur le plateau
        if (domino_selected.left == domino_selected.right) { //double à poser
            placed[dominos_state->placed_dominos_count +1].domino.rect.x = placed[i].domino.rect.x-30;
            placed[dominos_state->placed_dominos_count +1].domino.rect.y = placed[i].domino.rect.y-15 ;
            dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].vertical = true;
            dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].domino.rect.w = 30;                
            dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].domino.rect.h = 60;
        } else { //pas un double à poser
            placed[dominos_state->placed_dominos_count +1].domino.rect.x = placed[i].domino.rect.x-60;
            placed[dominos_state->placed_dominos_count +1].domino.rect.y = placed[i].domino.rect.y ;                
            dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].vertical = false;
            dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].domino.rect.w = 60;
            dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].domino.rect.h = 30;
        }
    } else { //double sur le plateau
        placed[dominos_state->placed_dominos_count +1].domino.rect.x = placed[i].domino.rect.x-60;
        placed[dominos_state->placed_dominos_count +1].domino.rect.y = placed[i].domino.rect.y+15 ;                
        dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].vertical = false;
        dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].domino.rect.w = 60;
        dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].domino.rect.h = 30;

    }

    placed[i].domino.left_available = false ;   
    placed[i+1].domino.right_available = false ;  
    dominos_state->placed_dominos_count += 1;


}

void place_selected_domino_upside_left(DominosGame* dominos_state, Domino domino_selected, int i) {
    PlacedDomino* placed = dominos_state->placed_dominos;

    placed[dominos_state->placed_dominos_count +1].domino = domino_selected;
    placed[dominos_state->placed_dominos_count +1].domino.left = domino_selected.right;
    placed[dominos_state->placed_dominos_count +1].domino.right = domino_selected.left;

        
    placed[dominos_state->placed_dominos_count +1].domino.rect.x = placed[i].domino.rect.x-60;

    placed[dominos_state->placed_dominos_count +1].domino.rect.y = placed[i].domino.rect.y ;                
    dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].vertical = false;
    dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].domino.rect.w = 60;
    dominos_state->placed_dominos[dominos_state->placed_dominos_count +1].domino.rect.h = 30;

    placed[i].domino.left_available = false ;   
    placed[dominos_state->placed_dominos_count +1].domino.right_available = false ;  
    dominos_state->placed_dominos_count += 1;

}

bool is_skip_turn_button_clicked(int mouse_x, int mouse_y, Game* game) {
    SDL_Rect button_rect = {10, game->window_height - BUTTON_HEIGHT - 10, BUTTON_WIDTH, BUTTON_HEIGHT};
    return (mouse_x >= button_rect.x && mouse_x <= button_rect.x + BUTTON_WIDTH &&
            mouse_y >= button_rect.y && mouse_y <= button_rect.y + BUTTON_HEIGHT);
}



void handle_dominos_events(Game* game, SDL_Event* event) {
    int mouseX, mouseY;
    DominosGame* dominos_state = get_dominos_game_state();

        switch (event->type) {
            case SDL_QUIT:
        game->running = false; 
        return; 


        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_ESCAPE) {
                if (!dominos_state->quit_dialog.is_visible) {
                    dominos_state->quit_dialog.is_visible = true;
                } else {
                    game->state = GAME_STATE_MENU;
                }
            }
            break;


        case SDL_MOUSEBUTTONDOWN:
            mouseX = event->button.x;
            mouseY = event->button.y;

            //Vérifier si une boîte de dialogue est ouverte
            if (dominos_state->quit_dialog.is_visible) {
                if (mouseX >= dominos_state->quit_dialog.yes_button.x &&
                    mouseX <= dominos_state->quit_dialog.yes_button.x + dominos_state->quit_dialog.yes_button.w &&
                    mouseY >= dominos_state->quit_dialog.yes_button.y &&
                    mouseY <= dominos_state->quit_dialog.yes_button.y + dominos_state->quit_dialog.yes_button.h) {
                    game->state = GAME_STATE_MENU;
                    return;
                }

                if (mouseX >= dominos_state->quit_dialog.no_button.x &&
                    mouseX <= dominos_state->quit_dialog.no_button.x + dominos_state->quit_dialog.no_button.w &&
                    mouseY >= dominos_state->quit_dialog.no_button.y &&
                    mouseY <= dominos_state->quit_dialog.no_button.y + dominos_state->quit_dialog.no_button.h) {
                    dominos_state->quit_dialog.is_visible = false;
                    return;
                }
                return;
            }

            // Vérifier si le bouton "Passer son tour" a été cliqué
            if (is_skip_turn_button_clicked(mouseX, mouseY, game)) {
                dominos_state->current_player = (dominos_state->current_player + 1) % dominos_state->nbr_joueurs;
                return;
            }

            //Vérifier si un domino placé sur le plateau est cliqué par l'utilisateur
            PlacedDomino* placed = dominos_state->placed_dominos;
            for(int i =0; i < 27; i++){
                SDL_Rect* rect = &placed[i].domino.rect;
                if (mouseX >= rect->x && mouseX <= rect->x + rect->w &&
                    mouseY >= rect->y && mouseY <= rect->y + rect->h) {                        
                    if (!placed[i].domino.selected){
                        placed[i].domino.selected = true;
                    } else {
                        placed[i].domino.selected = false;
                    }
                } 
            }

            //Vérifier si un domino de la main du joueur courant est cliqué par l'utilisateur et s'il est possible de jouer un coup
            if (dominos_state->current_player == 0) {
                for (int i = 0; i < dominos_state->hand_size; i++) {
                    SDL_Rect* rect = &dominos_state->player_hand[i].rect;
                    if (mouseX >= rect->x && mouseX <= rect->x + rect->w &&
                        mouseY >= rect->y && mouseY <= rect->y + rect->h) {
                        
                        if (dominos_state->player_hand[i].selected){
                            if(dominos_state->plateau_vide == true) {
                                place_selected_domino_middle(dominos_state, dominos_state->player_hand[i]);
                                dominos_state->player_hand[i].placed = true;
                                dominos_state->score[0] += dominos_state->player_hand[i].left + dominos_state->player_hand[i].right;
                                dominos_state->plateau_vide = false;
                                dominos_state->placed_dominos_count = 1;
                                dominos_state->current_player = dominos_state->ordre_joueurs[1];
                            } else{
                                PlacedDomino* placed = dominos_state->placed_dominos;
                                bool trouve = false;
                                int j = 0;
                                while(!trouve){                        
                                    if (placed[j].domino.selected){
                                        if(dominos_state->player_hand[i].left == placed[j].domino.right && placed[j].domino.right_available){
                                            place_selected_domino_right(dominos_state, dominos_state->player_hand[i], j);
                                            dominos_state->player_hand[j].placed = true;
                                            dominos_state->score[i] += dominos_state->player_hand[i].left + dominos_state->player_hand[i].right;
                                            placed[j].domino.selected = false;
                                            trouve = true;
                                            dominos_state->current_player =(dominos_state->current_player +1) % (dominos_state->nbr_joueurs);
                                        } else if (dominos_state->player_hand[i].right == placed[j].domino.left && placed[j].domino.left_available){
                                            place_selected_domino_left(dominos_state, dominos_state->player_hand[i], j);
                                            dominos_state->player_hand[j].placed = true;
                                            dominos_state->score[i] += dominos_state->player_hand[i].left + dominos_state->player_hand[i].right;
                                            placed[j].domino.selected = false;
                                            trouve = true;
                                            dominos_state->current_player =(dominos_state->current_player +1) % (dominos_state->nbr_joueurs);
                                        } else if (dominos_state->player_hand[i].right == placed[j].domino.right && placed[j].domino.right_available){
                                            place_selected_domino_upside_right(dominos_state, dominos_state->player_hand[i], j);
                                            dominos_state->player_hand[j].placed = true;
                                            dominos_state->score[i] += dominos_state->player_hand[i].left + dominos_state->player_hand[i].right;
                                            placed[j].domino.selected = false;
                                            trouve = true;
                                            dominos_state->current_player =(dominos_state->current_player +1) % (dominos_state->nbr_joueurs);
                                        } else if(dominos_state->player_hand[i].left == placed[j].domino.left && placed[j].domino.left_available){
                                            place_selected_domino_upside_left(dominos_state, dominos_state->player_hand[i], j);
                                            dominos_state->player_hand[j].placed = true;
                                            dominos_state->score[i] += dominos_state->player_hand[i].left + dominos_state->player_hand[i].right;
                                            placed[j].domino.selected = false;
                                            trouve = true;
                                            dominos_state->current_player =(dominos_state->current_player +1) % (dominos_state->nbr_joueurs);
                                        }
                                        
                                    } 
                                    j+=1;
                                } 

                            }
                                
                            dominos_state->player_hand[i].selected = false;
                        } else {
                            for (int j = 0; j < dominos_state->hand_size; j++) {
                                if (j != i) {
                                    dominos_state->player_hand[j].selected = false;
                                }
                            }
                            dominos_state->player_hand[i].selected = true;
                        }
                        break;
                    }
                }
                } else {
                for (int i = 0; i < dominos_state->hand_size; i++) {
                    SDL_Rect* rect = &dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].rect;
                    if (mouseX >= rect->x && mouseX <= rect->x + rect->w &&
                        mouseY >= rect->y && mouseY <= rect->y + rect->h) {
                        if (dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].selected) {
                            if(dominos_state->plateau_vide == true){
                                place_selected_domino_middle(dominos_state, dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i]);
                                dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].placed = true;
                                dominos_state->score[dominos_state->current_player] += dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].left + dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].right;
                                dominos_state->plateau_vide = false;
                                dominos_state->placed_dominos_count = 1;
                                dominos_state->current_player = dominos_state->ordre_joueurs[1];

                            } else{
                                PlacedDomino* placed = dominos_state->placed_dominos;
                                bool trouve = false;
                                int j = 0;
                                while(!trouve){                       
                                    if (placed[j].domino.selected){
                                        if(dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].left == placed[j].domino.right && placed[j].domino.right_available){
                                        place_selected_domino_right(dominos_state, dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i],j);
                                        dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].placed = true;
                                        dominos_state->score[dominos_state->current_player] += dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].left + dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].right;
                                        placed[j].domino.selected = false;
                                        trouve = true;
                                        dominos_state->current_player = (dominos_state->current_player+1) % (dominos_state->nbr_joueurs);
                                        } else if (dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].right == placed[j].domino.left && placed[j].domino.left_available){
                                            place_selected_domino_left(dominos_state, dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i],j);
                                            dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].placed = true;
                                            dominos_state->score[dominos_state->current_player] += dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].left + dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].right;
                                            placed[j].domino.selected = false;
                                            trouve = true;
                                            dominos_state->current_player = (dominos_state->current_player+1) % (dominos_state->nbr_joueurs);
                                        } else if (dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].right == placed[j].domino.right && placed[j].domino.right_available){
                                            place_selected_domino_upside_right(dominos_state, dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i],j);
                                            dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].placed = true;
                                            dominos_state->score[dominos_state->current_player] += dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].left + dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].right;
                                            placed[j].domino.selected = false;
                                            trouve = true;
                                            dominos_state->current_player = (dominos_state->current_player+1) % (dominos_state->nbr_joueurs);
                                        } else if (dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].left == placed[j].domino.left && placed[j].domino.left_available){
                                            place_selected_domino_upside_left(dominos_state, dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i],j);
                                            dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].placed = true;
                                            dominos_state->score[dominos_state->current_player] += dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].left + dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].right;
                                            placed[j].domino.selected = false;
                                            trouve = true;
                                            dominos_state->current_player = (dominos_state->current_player+1) % (dominos_state->nbr_joueurs);
                                        }
                                    } 
                                    j+=1;
                                } 
                            }
                            
                            dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].selected = false;

                        } else {
                            for (int j = 0; j < dominos_state->hand_size; j++) {
                                if (j != i) {
                                    dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+j].selected = false;
                                }
                            }
                            dominos_state->opponent_hand[(dominos_state->current_player-1)*dominos_state->hand_size+i].selected = true;

                        }
                        break;
                    }
                }

            }
    }
}


