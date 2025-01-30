#ifndef TRIOMINO_GAME_H
#define TRIOMINO_GAME_H

#include "triomino_types.h"
#include "../game.h"
#include "../player_setup.h"


TriominoGame* get_triomino_game_state();
void triomino_init(Game* game, int num_players);
void triomino_cleanup(Game* game);
void handle_mouse_click(Game* game, TriominoGame* triomino_state, int x, int y);
void end_triomino_game(Game* game, ConfigurationJoueurs* config);

#endif 
