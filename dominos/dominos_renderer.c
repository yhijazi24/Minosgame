#include <SDL2/SDL_ttf.h>
#include "dominos_types.h"
#include "dominos_game.h"
#include "dominos_renderer.h"
#include "../player_setup.h"
#include <stdio.h>
#define DOT_RADIUS 2.5
static TTF_Font* font = NULL;

#define BUTTON_WIDTH 170
#define BUTTON_HEIGHT 50
#define BUTTON_SPACING 10

void draw_skip_turn_button(Game* game) {
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    SDL_Rect button_rect = {10, game->window_height - BUTTON_HEIGHT - 10, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_RenderFillRect(game->renderer, &button_rect);

    TTF_Font* font = TTF_OpenFont("assets/fonts/Arial.ttf", 20);
    if (font) {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Passer son tour", textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);

        SDL_Rect text_rect = {
            button_rect.x + (button_rect.w - surface->w) / 2,
            button_rect.y + (button_rect.h - surface->h) / 2,
            surface->w,
            surface->h
        };

        SDL_RenderCopy(game->renderer, texture, NULL, &text_rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }
}

bool init_dominos_renderer(Game* game) {
    (void)game; 
    font = TTF_OpenFont("assets/fonts/Arial.ttf", 24);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }
    return true;
}
void cleanup_dominos_renderer(Game* game) {
    (void)game; 
    if (font) {
        TTF_CloseFont(font);
        font = NULL;
    }
}

void render_player_info(Game* game, int player, int x, int y, ConfigurationJoueurs *config, DominosGame* dominos_game) {
    TTF_Font* font = TTF_OpenFont("assets/fonts/Arial.ttf", 24);
    if (font) {
        SDL_Color textColor = {255, 255, 255, 255};
        char player_info[50];
        snprintf(player_info, sizeof(player_info), "%s: %d", 
                 config->nomsJoueurs[player - 1], dominos_game->score[player-1]);

        SDL_Surface* surface = TTF_RenderText_Solid(font, player_info, textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);

        SDL_Rect text_rect;
        double angle = 0.0;

        if (player == 1) {
            text_rect = (SDL_Rect){
                .x = x - 180,
                .y = y + (DOMINO_HEIGHT / 2) - (surface->h / 2) - 10,
                .w = surface->w,
                .h = surface->h
            };
        } else if (player == 2) {
            text_rect = (SDL_Rect){
                .x = x - 180,
                .y = y + (DOMINO_HEIGHT / 2) - (surface->h / 2) - 10,
                .w = surface->w,
                .h = surface->h
            };
        } else if (player == 3) {
            text_rect = (SDL_Rect){
                .x = x + (DOMINO_HEIGHT / 2) - (surface->w / 2) - 30,
                .y = y + 250,
                .w = surface->w,
                .h = surface->h
            };
            angle = 0.0;
        } else if (player == 4) {
            text_rect = (SDL_Rect){
                .x = x + (DOMINO_HEIGHT / 2) - (surface->w / 2),
                .y = y + 250,
                .w = surface->w,
                .h = surface->h
            };
            angle = 0.0;
        }

        SDL_RenderCopyEx(game->renderer, texture, NULL, &text_rect, angle, NULL, SDL_FLIP_NONE);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }
}

void render_order_player(DominosGame* dominos_game, Game* game) {
    TTF_Font* font = TTF_OpenFont("assets/fonts/Arial.ttf", 24);
    SDL_Color textColor = {255, 255, 255, 255}; 
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect text_rect;

    int start_x = game->window_width - 150;  
    int start_y = 600;
    int line_spacing = 30;

    surface = TTF_RenderText_Blended(font, "Ordre de jeu :", textColor);
    if (!surface) {
        printf("Erreur SDL_ttf: %s\n", TTF_GetError());
        return;
    }

    texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    if (!texture) {
        printf("Erreur SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    text_rect.x = start_x;
    text_rect.y = start_y - line_spacing; 
    text_rect.w = surface->w;
    text_rect.h = surface->h;

    SDL_RenderCopy(game->renderer, texture, NULL, &text_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // Afficher la liste des joueurs dans l'ordre
    for (int i = 0; i < dominos_game->nbr_joueurs; i++) {
        int player_index = dominos_game->ordre_joueurs[i];


    if (player_index < 0 || player_index >= dominos_game->nbr_joueurs) {
        continue; 
    }

    if (dominos_game->noms_joueurs[player_index] == NULL) {
        printf("Error: Player %d has no name assigned!\n", player_index);
        continue;
    }

    // ✅ Declare `affichage` here
    char affichage[50];

    snprintf(affichage, sizeof(affichage), "%d. %s", i + 1, dominos_game->noms_joueurs[player_index]);


        surface = TTF_RenderText_Blended(font, affichage, textColor);
        if (!surface) {
            printf("Erreur SDL_ttf: %s\n", TTF_GetError());
            continue;
        }

        texture = SDL_CreateTextureFromSurface(game->renderer, surface);
        if (!texture) {
            printf("Erreur SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
            SDL_FreeSurface(surface);
            continue;
        }

        text_rect.x = start_x;
        text_rect.y = start_y + i * line_spacing;
        text_rect.w = surface->w;
        text_rect.h = surface->h;

        SDL_RenderCopy(game->renderer, texture, NULL, &text_rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    //  Afficher le joueur actuel en dernière ligne
    int joueur_actuel_index = dominos_game->current_player; 
    char joueur_actuel_text[50];
    snprintf(joueur_actuel_text, sizeof(joueur_actuel_text), "Actuel : %s", dominos_game->noms_joueurs[joueur_actuel_index]);

    surface = TTF_RenderText_Blended(font, joueur_actuel_text, textColor);
    if (!surface) {
        printf("Erreur SDL_ttf: %s\n", TTF_GetError());
        return;
    }

    texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    if (!texture) {
        printf("Erreur SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    text_rect.x = start_x;
    text_rect.y = start_y + dominos_game->nbr_joueurs * line_spacing;
    text_rect.w = surface->w;
    text_rect.h = surface->h;

    SDL_RenderCopy(game->renderer, texture, NULL, &text_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}





static void draw_filled_circle(SDL_Renderer* renderer, int center_x, int center_y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, center_x + dx, center_y + dy);
            }
        }
    }
}


static void draw_dot(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    draw_filled_circle(renderer, x, y, DOT_RADIUS);
}


static void draw_number_dots(SDL_Renderer* renderer, int number, SDL_Rect half, bool rotated) {
    int center_x = half.x + half.w / 2;
    int center_y = half.y + half.h / 2;
    
    int offset_x = rotated ? half.h / 4 : half.w / 4;  
    int offset_y = rotated ? half.w / 4 : half.h / 4;  

    if (rotated) {
        
        switch (number) {
            case 1:
                draw_dot(renderer, center_x, center_y);
                break;
            case 2:
                draw_dot(renderer, center_x - offset_x, center_y);
                draw_dot(renderer, center_x + offset_x, center_y);
                break;
            case 3:
                draw_dot(renderer, center_x - offset_x, center_y - offset_y);
                draw_dot(renderer, center_x, center_y);
                draw_dot(renderer, center_x + offset_x, center_y + offset_y);
                break;
            case 4:
                draw_dot(renderer, center_x - offset_x, center_y - offset_y);
                draw_dot(renderer, center_x - offset_x, center_y + offset_y);
                draw_dot(renderer, center_x + offset_x, center_y - offset_y);
                draw_dot(renderer, center_x + offset_x, center_y + offset_y);
                break;
            case 5:
                draw_dot(renderer, center_x - offset_x, center_y - offset_y);
                draw_dot(renderer, center_x - offset_x, center_y + offset_y);
                draw_dot(renderer, center_x, center_y);
                draw_dot(renderer, center_x + offset_x, center_y - offset_y);
                draw_dot(renderer, center_x + offset_x, center_y + offset_y);
                break;
            case 6:
                draw_dot(renderer, center_x - offset_x, center_y - offset_y);
                draw_dot(renderer, center_x - offset_x, center_y);
                draw_dot(renderer, center_x - offset_x, center_y + offset_y);
                draw_dot(renderer, center_x + offset_x, center_y - offset_y);
                draw_dot(renderer, center_x + offset_x, center_y);
                draw_dot(renderer, center_x + offset_x, center_y + offset_y);
                break;
        }
    } else {
        
        switch (number) {
            case 1:
                draw_dot(renderer, center_x, center_y);
                break;
            case 2:
                draw_dot(renderer, center_x, center_y - offset_y);
                draw_dot(renderer, center_x, center_y + offset_y);
                break;
            case 3:
                draw_dot(renderer, center_x, center_y - offset_y);
                draw_dot(renderer, center_x, center_y);
                draw_dot(renderer, center_x, center_y + offset_y);
                break;
            case 4:
                draw_dot(renderer, center_x - offset_x, center_y - offset_y);
                draw_dot(renderer, center_x + offset_x, center_y - offset_y);
                draw_dot(renderer, center_x - offset_x, center_y + offset_y);
                draw_dot(renderer, center_x + offset_x, center_y + offset_y);
                break;
            case 5:
                draw_dot(renderer, center_x - offset_x, center_y - offset_y);
                draw_dot(renderer, center_x + offset_x, center_y - offset_y);
                draw_dot(renderer, center_x, center_y);
                draw_dot(renderer, center_x - offset_x, center_y + offset_y);
                draw_dot(renderer, center_x + offset_x, center_y + offset_y);
                break;
            case 6:
                draw_dot(renderer, center_x - offset_x, center_y - offset_y);
                draw_dot(renderer, center_x + offset_x, center_y - offset_y);
                draw_dot(renderer, center_x - offset_x, center_y);
                draw_dot(renderer, center_x + offset_x, center_y);
                draw_dot(renderer, center_x - offset_x, center_y + offset_y);
                draw_dot(renderer, center_x + offset_x, center_y + offset_y);
                break;
        }
    }
}

void render_quit_dialog(Game* game, QuitDialogt* dialog) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 180);
    SDL_Rect bg = { game->window_width / 4, game->window_height / 3, game->window_width / 2, game->window_height / 3 };
    SDL_RenderFillRect(game->renderer, &bg);

    TTF_Font* font = TTF_OpenFont("assets/fonts/Arial.ttf", 24);
    if (!font) {
        printf("Erreur chargement de la police: %s\n", TTF_GetError());
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};

    // Afficher le texte de confirmation
    SDL_Surface* surface = TTF_RenderText_Blended(font, "Voulez-vous quitter ?", textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_Rect text_rect = { bg.x + (bg.w - surface->w) / 2, bg.y + 20, surface->w, surface->h };
    SDL_RenderCopy(game->renderer, texture, NULL, &text_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    int button_width = 100;
    int button_height = 50;
    int button_spacing = 20;

    dialog->yes_button.w = dialog->no_button.w = button_width;
    dialog->yes_button.h = dialog->no_button.h = button_height;

    dialog->yes_button.x = bg.x + (bg.w / 2) - (button_width + button_spacing);
    dialog->yes_button.y = bg.y + bg.h - button_height - 20;

    dialog->no_button.x = bg.x + (bg.w / 2) + button_spacing;
    dialog->no_button.y = bg.y + bg.h - button_height - 20;

    SDL_SetRenderDrawColor(game->renderer, 200, 0, 0, 255);
    SDL_RenderFillRect(game->renderer, &dialog->yes_button);
    SDL_SetRenderDrawColor(game->renderer, 0, 200, 0, 255);
    SDL_RenderFillRect(game->renderer, &dialog->no_button);


    surface = TTF_RenderText_Blended(font, "Oui", textColor);
    texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_Rect yes_rect = { dialog->yes_button.x + (button_width - surface->w) / 2, dialog->yes_button.y + (button_height - surface->h) / 2, surface->w, surface->h };
    SDL_RenderCopy(game->renderer, texture, NULL, &yes_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Blended(font, "Non", textColor);
    texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_Rect no_rect = { dialog->no_button.x + (button_width - surface->w) / 2, dialog->no_button.y + (button_height - surface->h) / 2, surface->w, surface->h };
    SDL_RenderCopy(game->renderer, texture, NULL, &no_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    TTF_CloseFont(font);
}



void render_dominos(Game* game, int num_players, ConfigurationJoueurs *config) {
    DominosGame* dominos_state = get_dominos_game_state();

    SDL_SetRenderDrawColor(game->renderer, 34, 139, 34, 255);
    SDL_RenderClear(game->renderer);

    SDL_SetRenderDrawColor(game->renderer, 169, 169, 169, 255);
    SDL_RenderFillRect(game->renderer, &dominos_state->playing_area);

    for (int player = 1; player <= num_players; player++) {
        Domino* hand = (player == 1)
            ? dominos_state->player_hand
            : &dominos_state->opponent_hand[(player - 2) * dominos_state->hand_size];

        for (int i = 0; i < dominos_state->hand_size; i++) {
                
                if(!hand[i].placed){
                    SDL_Rect rect = hand[i].rect;
                    bool is_selected = hand[i].selected; 

                    //Changer la couleur de fond si sélectionné
                    if (is_selected) {
                        SDL_SetRenderDrawColor(game->renderer, 255, 215, 0, 255);
                    } else {
                        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
                    }
                    SDL_RenderFillRect(game->renderer, &rect);

                    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); 
                    SDL_RenderDrawRect(game->renderer, &rect);

                    // Si le domino est sélectionné, dessiner un contour rouge
                    if (is_selected) {
                        SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255); 
                        SDL_RenderDrawRect(game->renderer, &rect); 
                    }

                    
                    int middle_x = rect.x;
                    int middle_y = rect.y + rect.h / 2;
                    if (player == 3 || player == 4) {
                        
                        int middle_x = rect.x + rect.w / 2;
                        SDL_RenderDrawLine(game->renderer, middle_x, rect.y, middle_x, rect.y + rect.h);
                    } else {
                        
                        int middle_y = rect.y + rect.h / 2;
                        SDL_RenderDrawLine(game->renderer, rect.x, middle_y, rect.x + rect.w, middle_y);
                    }
                    SDL_Rect first_half, second_half;

                    if (player == 3 || player == 4) {
                        
                        first_half = (SDL_Rect){rect.x, rect.y, rect.w / 2, rect.h};
                        second_half = (SDL_Rect){rect.x + rect.w / 2, rect.y, rect.w / 2, rect.h};
                    } else {
                        
                        first_half = (SDL_Rect){rect.x, rect.y, rect.w, rect.h / 2};
                        second_half = (SDL_Rect){rect.x, rect.y + rect.h / 2, rect.w, rect.h / 2};
                    }


                    draw_number_dots(game->renderer, hand[i].left, first_half, (player == 3 || player == 4));
                    draw_number_dots(game->renderer, hand[i].right, second_half, (player == 3 || player == 4));

                }
        }   
        
        if (player == 1) {
            render_player_info(game, player, (game->window_width - (DOMINO_WIDTH + 10) * dominos_state->hand_size) / 2, game->window_height - 100, config, dominos_state);
        } else if (player == 2) {
            render_player_info(game, player, (game->window_width - (DOMINO_WIDTH + 10) * dominos_state->hand_size) / 2, 0, config, dominos_state);
        } else if (player == 3) {
            render_player_info(game, player, game->window_width - 50, (game->window_height - (DOMINO_WIDTH + 10) * dominos_state->hand_size) / 2, config, dominos_state);
        } else if (player == 4) {
            render_player_info(game, player, 50, (game->window_height - (DOMINO_WIDTH + 10) * dominos_state->hand_size) / 2, config, dominos_state);
        }
    }
    for(int i =0; i < 28; i++){
        Domino* domino = &dominos_state->placed_dominos[i].domino;
        SDL_Rect rect = domino->rect;

        if (domino->selected) {
            SDL_SetRenderDrawColor(game->renderer, 255, 215, 0, 255);
        } else {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        }
        SDL_RenderFillRect(game->renderer, &rect);
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(game->renderer, &rect);

        if (domino->selected) {
            SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255); 
            SDL_RenderDrawRect(game->renderer, &rect);
        }

        int middle_x = rect.x;
        int middle_y = rect.y + rect.h / 2;

        // Ajuster les dimensions pour l'orientation verticale/horizontale
        if (dominos_state->placed_dominos[i].vertical) {
            int middle_y = rect.y + rect.h / 2;
            SDL_RenderDrawLine(game->renderer, rect.x,middle_y, rect.x + rect.w, middle_y);
        } else {
            int middle_x = rect.x + rect.w / 2;
            SDL_RenderDrawLine(game->renderer, middle_x, rect.y, middle_x, rect.y + rect.h);
        }
        SDL_Rect first_half, second_half;
        if (dominos_state->placed_dominos[i].vertical) {
            first_half = (SDL_Rect){rect.x, rect.y, rect.w, rect.h / 2};
            second_half = (SDL_Rect){rect.x, rect.y + rect.h / 2, rect.w, rect.h / 2};
        } else {
            first_half = (SDL_Rect){rect.x, rect.y, rect.w / 2, rect.h};
            second_half = (SDL_Rect){rect.x + rect.w / 2, rect.y, rect.w / 2, rect.h};
        }
        draw_number_dots(game->renderer, domino->left, first_half, dominos_state->placed_dominos[i].vertical);
        draw_number_dots(game->renderer, domino->right, second_half, dominos_state->placed_dominos[i].vertical);

}


    if (dominos_state->quit_dialog.is_visible) {
        render_quit_dialog(game, &dominos_state->quit_dialog);
    }


    SDL_RenderPresent(game->renderer);
}


