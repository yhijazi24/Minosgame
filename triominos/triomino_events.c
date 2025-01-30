#include <SDL2/SDL.h>
#include "triomino_events.h"
#include "triomino_game.h"
#include "triomino_types.h"


void handle_triomino_events(Game* game, SDL_Event* event) {
    int mouseX, mouseY; 
    TriominoGame* triomino_state = get_triomino_game_state(); 

    switch (event->type) {
        case SDL_QUIT:
            game->running = false;
            return;

        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_ESCAPE) {
                if (!triomino_state->quit_dialog.is_visible) {
                    triomino_state->quit_dialog.is_visible = true;
                } else {
                    game->state = GAME_STATE_MENU;
                }
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseX = event->button.x;
            mouseY = event->button.y;

            // Vérifier si une boîte de dialogue est ouverte
            if (triomino_state->quit_dialog.is_visible) {
                if (mouseX >= triomino_state->quit_dialog.yes_button.x &&
                    mouseX <= triomino_state->quit_dialog.yes_button.x + triomino_state->quit_dialog.yes_button.w &&
                    mouseY >= triomino_state->quit_dialog.yes_button.y &&
                    mouseY <= triomino_state->quit_dialog.yes_button.y + triomino_state->quit_dialog.yes_button.h) {
                    game->state = GAME_STATE_MENU;
                    return;
                }

                if (mouseX >= triomino_state->quit_dialog.no_button.x &&
                    mouseX <= triomino_state->quit_dialog.no_button.x + triomino_state->quit_dialog.no_button.w &&
                    mouseY >= triomino_state->quit_dialog.no_button.y &&
                    mouseY <= triomino_state->quit_dialog.no_button.y + triomino_state->quit_dialog.no_button.h) {
                    triomino_state->quit_dialog.is_visible = false;
                    return;
                }
            }
            break;
    }
}
