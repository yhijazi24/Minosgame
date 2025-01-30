#ifndef DOMINOS_RENDERER_H
#define DOMINOS_RENDERER_H

#include "../game.h"
#include <stdbool.h>
#include "../player_setup.h"

bool init_dominos_renderer(Game* game);
void cleanup_dominos_renderer(Game* game);
void render_player_info(Game* game, int player, int x, int y, ConfigurationJoueurs *config, DominosGame* dominos_game);
void render_order_player(DominosGame* dominos_game, Game* game);
void draw_skip_turn_button(Game* game);
static void draw_filled_circle(SDL_Renderer* renderer, int center_x, int center_y, int radius);
static void draw_dot(SDL_Renderer* renderer, int x, int y);
static void draw_number_dots(SDL_Renderer* renderer, int number, SDL_Rect half, bool rotated);
void render_dominos(Game* game, int num_players, ConfigurationJoueurs *config);

#endif 
