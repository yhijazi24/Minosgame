#ifndef TRIOMINO_RENDERER_H
#define TRIOMINO_RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "triomino_types.h"
#include "triomino_game.h"
#include "../player_setup.h"


void dessiner_triomino(SDL_Renderer* renderer, TTF_Font* font, Triomino* triomino, int x, int y, int size, bool rotate);  
void draw_skip_turn_buttont(Game* game);
void render_triomino_plateau(Game* game, TriominoGame* triomino_state, ConfigurationJoueurs *config);
void render_triominos(Game* game, ConfigurationJoueurs *config);
void render_quit_dialogt(Game* game, QuitDialog* dialog);

#endif 
