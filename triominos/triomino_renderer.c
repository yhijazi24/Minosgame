#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "triomino_renderer.h"
#include "triomino_game.h"
#include "triomino_types.h"
#include "../player_setup.h"

#include <stdio.h>

#define TRIOMINO_SIZE 60
#define SPACING 15
#define BUTTON_WIDTH 170
#define BUTTON_HEIGHT 50
#define BUTTON_SPACING 10

static TTF_Font* skip_button_font = NULL; 

void draw_skip_turn_buttont(Game* game) {
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    SDL_Rect button_rect = {10, game->window_height - BUTTON_HEIGHT - 10, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_RenderFillRect(game->renderer, &button_rect);

    // 🔹 Load font only once and reuse it
    if (!skip_button_font) {
        skip_button_font = TTF_OpenFont("assets/fonts/Arial.ttf", 20);
        if (!skip_button_font) {
            printf("Erreur chargement de la police: %s\n", TTF_GetError());
            return;
        }
    }

    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(skip_button_font, "Passer son tour", textColor);
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
}


void draw_filled_triangle(SDL_Renderer* renderer, int x, int y, int size, bool rotate) {
    int base_offset = size / 8;

    SDL_Vertex vertices[3] = {
        {{x, y}, {255, 255, 255, 255}, {0, 0}},  
        {{x - (size / 2 + base_offset), y + size}, {255, 255, 255, 255}, {0, 0}}, 
        {{x + (size / 2 + base_offset), y + size}, {255, 255, 255, 255}, {0, 0}}  
    };

    SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, vertices[0].position.x, vertices[0].position.y,
                       vertices[1].position.x, vertices[1].position.y);
    SDL_RenderDrawLine(renderer, vertices[1].position.x, vertices[1].position.y,
                       vertices[2].position.x, vertices[2].position.y);
    SDL_RenderDrawLine(renderer, vertices[2].position.x, vertices[2].position.y,
                       vertices[0].position.x, vertices[0].position.y);
}



void dessiner_triomino(SDL_Renderer* renderer, TTF_Font* font, Triomino* triomino, int x, int y, int size, bool rotate) {
    if (!triomino) return;

    draw_filled_triangle(renderer, x, y, size, false); 

    SDL_Color textColor = {0, 0, 0, 255};
    char values[3][5];

    snprintf(values[0], sizeof(values[0]), "%d", triomino->value1);
    snprintf(values[1], sizeof(values[1]), "%d", triomino->value2);
    snprintf(values[2], sizeof(values[2]), "%d", triomino->value3);

    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect text_rect;

    int text_positions[3][2] = {
        {x - size / 3, y + (size * 3) / 4}, 
        {x + size / 3, y + (size * 3) / 4}, 
        {x, y + size / 4}                   
    };

    for (int i = 0; i < 3; i++) {
        surface = TTF_RenderText_Blended(font, values[i], textColor);
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        text_rect = (SDL_Rect){
            .x = text_positions[i][0] - surface->w / 2,
            .y = text_positions[i][1] - surface->h / 2,
            .w = surface->w,
            .h = surface->h
        };

        SDL_RenderCopy(renderer, texture, NULL, &text_rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}


void render_triomino_plateau(Game* game, TriominoGame* triomino_state, ConfigurationJoueurs *config) {
    SDL_SetRenderDrawColor(game->renderer, 34, 139, 34, 255); 
    SDL_RenderClear(game->renderer);

    SDL_SetRenderDrawColor(game->renderer, 169, 169, 169, 255); 
    SDL_RenderFillRect(game->renderer, &triomino_state->playing_area);

    TTF_Font* font = TTF_OpenFont("assets/fonts/Arial.ttf", 17);
    if (!font) {
        SDL_Log("Failed to load font for rendering: %s", TTF_GetError());
        return;
    }

    int spacing = TRIOMINO_SIZE + SPACING;
    int triominoes_per_player = (triomino_state->nombreJoueurs >= 3) ? 6 : 7;

    for (int player = 1; player <= triomino_state->nombreJoueurs; player++) {
        Triomino* hand = triomino_state->player_hands[player - 1];

        int x, y;
        bool rotate_text = false;
        if (player == 1) {
            x = (game->window_width - spacing * triominoes_per_player) / 2 + 70;
            y = game->window_height - TRIOMINO_SIZE - 10;
        } else if (player == 2) {
            x = (game->window_width - spacing * triominoes_per_player) / 2 + 70;
            y = 10;
        } else if (player == 3) {
            x = game->window_width - TRIOMINO_SIZE - 15;
            y = (game->window_height - spacing * triominoes_per_player) / 2;
            rotate_text = true; 
        } else if (player == 4) {
            x = 110;
            y = (game->window_height - spacing * triominoes_per_player) / 2;
            rotate_text = true; 
        }

        int i = 0;
        while (hand) {
            dessiner_triomino(game->renderer, font, hand, x + (player <= 2 ? i * spacing : 0), y + (player > 2 ? i * spacing : 0), TRIOMINO_SIZE, false);
            hand = hand->suivant;
            i++;
        }

        
        SDL_Color white = {255, 255, 255, 255};
        char player_info[50];
        snprintf(player_info, sizeof(player_info), "%s: %d", 
                 config->nomsJoueurs[player - 1], 0);

        SDL_Surface* text_surface = TTF_RenderText_Blended(font, player_info, white);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(game->renderer, text_surface);

        SDL_Rect text_rect;
        if (player == 1) {
            text_rect = (SDL_Rect){x - 120, y + 20, text_surface->w, text_surface->h};  
        } else if (player == 2) {
            text_rect = (SDL_Rect){x - 120, y + 20, text_surface->w, text_surface->h};  
        } else if (player == 3) {
            text_rect = (SDL_Rect){x + 20, y + (spacing * triominoes_per_player), text_surface->w, text_surface->h}; 
        } else if (player == 4) {
            text_rect = (SDL_Rect){x - 80, y + (spacing * triominoes_per_player), text_surface->w, text_surface->h}; 
        }

        SDL_RenderCopy(game->renderer, text_texture, NULL, &text_rect);

        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }

    TTF_CloseFont(font);
}

void render_quit_dialogt(Game* game, QuitDialog* dialog) {
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

void render_triominos(Game* game, ConfigurationJoueurs *config) {
    TriominoGame* triomino_state = get_triomino_game_state();
    render_triomino_plateau(game, triomino_state, config);

        if (triomino_state->quit_dialog.is_visible) {
        render_quit_dialogt(game, &triomino_state->quit_dialog);
 
   }
   draw_skip_turn_buttont(game);
       SDL_RenderPresent(game->renderer);

}
