#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dominos_game.h"
#include "dominos_types.h"
#include "dominos_renderer.h"
#include "../game_score.h"
#include "../player_setup.h"

#define DOMINO_WIDTH 30
#define DOMINO_HEIGHT 60
#define PADDING 5

static DominosGame dominos_state = {0};

void initialize_domino_deck(DominosGame* game) {
    int deck_index = 0;

    for (int left = 0; left <= 6; left++) {

        for (int right = left; right <= 6; right++) {
            game->deck[deck_index].left = left;
            game->deck[deck_index].right = right;
            game->deck[deck_index].left_available = true;
            game->deck[deck_index].right_available = true;
            game->deck[deck_index].visible = true;
            game->deck[deck_index].selected = false;
            deck_index++;
        }
    }

    game->deck_size = 28;
}

void shuffle_domino_deck(DominosGame* game){
    if (game->deck_size>1){
        for(int i = game->deck_size-1; i > 0; i--){
            int j = rand()%(i+1);
            Domino temp = game->deck[i];
            game->deck[i] =  game->deck[j];
            game->deck[j]= temp;

        }
    }
}

void determine_order(DominosGame* dominos_game, int num_players){
    int dominoes_per_player = (num_players >= 3) ? 6 : 7;
    int indice_premier_joueur_double = -1;
    int indice_premier_joueur_non_double = -1;
    int non_double_max_trouve = -1;
    int double_max_trouve = -1;

    for(int i = 0; i < dominoes_per_player; i++){
        if (dominos_game->player_hand[i].left == dominos_game->player_hand[i].right && 
            dominos_game->player_hand[i].right > double_max_trouve) {
            double_max_trouve = dominos_game->player_hand[i].right;
            indice_premier_joueur_double = 0;
        }
        if (dominos_game->player_hand[i].left + dominos_game->player_hand[i].right > non_double_max_trouve) {
            non_double_max_trouve = dominos_game->player_hand[i].left + dominos_game->player_hand[i].right;
            indice_premier_joueur_non_double = 0;
        }
    }

    for(int j = 0; j < num_players - 1; j++){
        for(int i = 0; i < dominoes_per_player; i++){
            int index = j * dominos_game->hand_size + i;
            if (dominos_game->opponent_hand[index].left == dominos_game->opponent_hand[index].right &&
                dominos_game->opponent_hand[index].right > double_max_trouve) {
                double_max_trouve = dominos_game->opponent_hand[index].right;
                indice_premier_joueur_double = j + 1;
            }
            if (dominos_game->opponent_hand[index].left + dominos_game->opponent_hand[index].right > non_double_max_trouve) {
                non_double_max_trouve = dominos_game->opponent_hand[index].left + dominos_game->opponent_hand[index].right;
                indice_premier_joueur_non_double = j + 1;
            }
        }
    }

    // Définir l'ordre des joueurs
    if(double_max_trouve == -1) { // Pas de double trouvé
        for(int i = 0; i < num_players; i++) {
            dominos_game->ordre_joueurs[i] = (indice_premier_joueur_non_double + i) % num_players;
        }
    } else { // Un double a été trouvé
        for(int i = 0; i < num_players; i++) {
            dominos_game->ordre_joueurs[i] = (indice_premier_joueur_double + i) % num_players;
        }
    }
}


void select_player_hand(Game* game, DominosGame* dominos_game, Domino* hand, bool is_visible, int player, int num_players) {
    int dominoes_per_player = (num_players >= 3) ? 6 : 7;

    int x_position = 0;
    int y_position = 0;
    bool rotate = false; 
    int rotation_angle = 0; 
    int spacing = 10; 

    
    if (player == 1) { 
        x_position = (game->window_width - (DOMINO_WIDTH + spacing) * dominoes_per_player + spacing) / 2; 
        y_position = game->window_height - DOMINO_HEIGHT - 10; 
    } else if (player == 2) { 
        x_position = (game->window_width - (DOMINO_WIDTH + spacing) * dominoes_per_player + spacing) / 2; 
        y_position = 10; 
    } else if (player == 3) { 
        x_position = game->window_width - DOMINO_HEIGHT - 50;
        y_position = (game->window_height - (DOMINO_WIDTH + spacing) * dominoes_per_player + spacing) / 2 - 150; 
        rotate = true;     
        rotation_angle = 90;
    } else if (player == 4) { 
        x_position = 50;
        y_position = (game->window_height - (DOMINO_WIDTH + spacing) * dominoes_per_player + spacing) / 2 - 150; 
        rotate = true;     
        rotation_angle = -90;
    }

    spacing = rotate ? DOMINO_HEIGHT + 10 : DOMINO_WIDTH + 10; 

    for (int i = 0; i < dominoes_per_player; i++) {
        hand[i] = dominos_game->deck[i];
        hand[i].selected = false;
        hand[i].visible = is_visible;
        hand[i].placed = false;

        if (rotate) {
            hand[i].rect = (SDL_Rect){
                .x = x_position,
                .y = y_position + i * spacing,
                .w = DOMINO_HEIGHT,
                .h = DOMINO_WIDTH
            };
        } else {
            hand[i].rect = (SDL_Rect){
                .x = x_position + i * spacing,
                .y = y_position,
                .w = DOMINO_WIDTH,
                .h = DOMINO_HEIGHT
            };
        }
    }

    
    memmove(dominos_game->deck, dominos_game->deck + dominoes_per_player, 
            sizeof(Domino) * (dominos_game->deck_size - dominoes_per_player));
    dominos_game->deck_size -= dominoes_per_player;
}





bool dominos_init(Game* game, int num_players, ConfigurationJoueurs* config) {
    dominos_state.nbr_joueurs = num_players;
    dominos_state.placed_dominos_count = 0;
    dominos_state.hand_size = (num_players >= 3) ? 6 : 7;
    dominos_state.placement_location_count = 0;
    for (int i = 0; i < 4; i++) {
        dominos_state.score[i]= 0;
        strcpy(dominos_state.noms_joueurs[i], config->nomsJoueurs[i]);
    }
    dominos_state.player_hand = malloc(sizeof(Domino) * dominos_state.hand_size);
    dominos_state.opponent_hand = malloc(sizeof(Domino) * dominos_state.hand_size * (num_players - 1));
    dominos_state.deck = malloc(sizeof(Domino) * 28);
    dominos_state.plateau_vide = true;

    if (!dominos_state.player_hand || !dominos_state.opponent_hand || !dominos_state.deck) {
        SDL_Log("Memory allocation failed during initialization.");
        return false;
    }

    initialize_domino_deck(&dominos_state);
    shuffle_domino_deck(&dominos_state);
    select_player_hand(game, &dominos_state, dominos_state.player_hand, true, 1, num_players);
    for (int i = 2; i <= num_players; i++) {
        select_player_hand(game, &dominos_state, dominos_state.opponent_hand + (i - 2) * dominos_state.hand_size, false, i, num_players);
    }
    determine_order(&dominos_state, num_players);
    dominos_state.current_player = dominos_state.ordre_joueurs[0];

    dominos_state.playing_area = (SDL_Rect){
        .x = (game->window_width - 800) / 2,
        .y = (game->window_height - 500) / 2,
        .w = 800,
        .h = 500
    };

    if (!init_dominos_renderer(game)) {
        SDL_Log("Dominos renderer initialization failed.");
        return false;
    }

    return true;
}


void dominos_cleanup(Game* game) {
    DominosGame* dominos_state = get_dominos_game_state();

    if (!dominos_state) return; 

    if (dominos_state->player_hand) {
        free(dominos_state->player_hand);
        dominos_state->player_hand = NULL;
    }

    #ifdef DYNAMIC_PLACED_DOMINOS
    if (dominos_state->placed_dominos) {
        free(dominos_state->placed_dominos);
        dominos_state->placed_dominos = NULL; 
    }
    #endif
    if (dominos_state->opponent_hand) {
        free(dominos_state->opponent_hand);
        dominos_state->opponent_hand = NULL;
    }
    free(dominos_state);
}



DominosGame* get_dominos_game_state(void) {
    return &dominos_state;
}

void calculate_placement_locations(DominosGame* game, Domino* selected_domino, PlacementLocation* locations, int* location_count) {
    *location_count = 0;

    
    if (game->placed_dominos_count == 0) {
        SDL_Rect center_location = {
            game->playing_area.x + (game->playing_area.w - selected_domino->rect.w) / 2,
            game->playing_area.y + (game->playing_area.h - selected_domino->rect.h) / 2,
            selected_domino->rect.w,
            selected_domino->rect.h
        };
        locations[0].location = center_location;
        locations[0].is_valid = true;
        *location_count = 1;
        return;
    }
} 

void end_dominos_game(Game* game, ConfigurationJoueurs* config) {
    DominosGame* dominos_state = get_dominos_game_state();

    if (dominos_state->nbr_joueurs <= 0) {
        return;
    }

    PlayerScore players[dominos_state->nbr_joueurs];

    for (int i = 0; i < dominos_state->nbr_joueurs; i++) {
        snprintf(players[i].username, 50, "%s", config->nomsJoueurs[i]);  
        players[i].score = dominos_state->score[i];  
    }

    save_scores_to_file("DOMINOS", players, dominos_state->nbr_joueurs);
}