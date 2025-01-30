#include <SDL2/SDL_ttf.h>
#include "game.h"
#include "menu.h"
#include "dominos/dominos_game.h"

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 50
#define BUTTON_PADDING 20

typedef enum {
    MENU_MAIN,
    MENU_RULES_SELECTION,
    MENU_RULES_DOMINOS,
    MENU_RULES_TRIOMINOS
} MenuState;

static MenuState menu_state = MENU_MAIN;

typedef struct {
    SDL_Rect rect;
    const char* text;
} Button;

static Button main_buttons[3];  
static Button rules_buttons[3];  
static Button back_button;  
static TTF_Font* font = NULL;

bool menu_init(Game* game) {
    font = TTF_OpenFont("assets/fonts/Arial.ttf", 24);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }

    int total_height = 3 * BUTTON_HEIGHT + 2 * BUTTON_PADDING;
    int start_y = (game->window_height - total_height) / 2;

    
    main_buttons[0] = (Button){(SDL_Rect){(game->window_width - BUTTON_WIDTH) / 2, start_y, BUTTON_WIDTH, BUTTON_HEIGHT}, "Dominos"};
    main_buttons[1] = (Button){(SDL_Rect){(game->window_width - BUTTON_WIDTH) / 2, start_y + BUTTON_HEIGHT + BUTTON_PADDING, BUTTON_WIDTH, BUTTON_HEIGHT}, "Triominos"};
    main_buttons[2] = (Button){(SDL_Rect){(game->window_width - BUTTON_WIDTH) / 2, start_y + 2 * (BUTTON_HEIGHT + BUTTON_PADDING), BUTTON_WIDTH, BUTTON_HEIGHT}, "Regles de jeux"};

    
    int rules_start_y = (game->window_height - (3 * BUTTON_HEIGHT + 2 * BUTTON_PADDING)) / 2;
    rules_buttons[0] = (Button){(SDL_Rect){(game->window_width - BUTTON_WIDTH) / 2, rules_start_y, BUTTON_WIDTH, BUTTON_HEIGHT}, "Regles de jeu Dominos"};
    rules_buttons[1] = (Button){(SDL_Rect){(game->window_width - BUTTON_WIDTH) / 2, rules_start_y + BUTTON_HEIGHT + BUTTON_PADDING, BUTTON_WIDTH, BUTTON_HEIGHT}, "Regles de jeu Triominos"};
    rules_buttons[2] = (Button){(SDL_Rect){(game->window_width - BUTTON_WIDTH) / 2, rules_start_y + 2 * (BUTTON_HEIGHT + BUTTON_PADDING), BUTTON_WIDTH, BUTTON_HEIGHT}, "Menu Principale"};

    
    back_button = (Button){(SDL_Rect){(game->window_width - BUTTON_WIDTH) / 2, game->window_height - BUTTON_HEIGHT - 50, BUTTON_WIDTH, BUTTON_HEIGHT}, "Menu"};

    return true;
}

void menu_cleanup(Game* game) {
    (void)game;
    if (font) {
        TTF_CloseFont(font);
        font = NULL;
    }
}

void handle_menu_events(Game* game, SDL_Event* event) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event->button.x;
        int mouseY = event->button.y;

        if (menu_state == MENU_MAIN) {
            for (int i = 0; i < 3; i++) {
                if (mouseX >= main_buttons[i].rect.x && mouseX <= main_buttons[i].rect.x + main_buttons[i].rect.w &&
                    mouseY >= main_buttons[i].rect.y && mouseY <= main_buttons[i].rect.y + main_buttons[i].rect.h) {
                    
                    if (i == 0) {
                        game->game_mode = GAME_MODE_DOMINOS;
                        game->state = CONFIG_JOUEURS;
                    } else if (i == 1) {
                        game->game_mode = GAME_MODE_TRIOMINOS;
                        game->state = CONFIG_JOUEURS;
                    } else if (i == 2) {
                        menu_state = MENU_RULES_SELECTION;  
                    }
                    break;
                }
            }
        } else if (menu_state == MENU_RULES_SELECTION) {
            for (int i = 0; i < 3; i++) {
                if (mouseX >= rules_buttons[i].rect.x && mouseX <= rules_buttons[i].rect.x + rules_buttons[i].rect.w &&
                    mouseY >= rules_buttons[i].rect.y && mouseY <= rules_buttons[i].rect.y + rules_buttons[i].rect.h) {
                    
                    if (i == 0) {
                        menu_state = MENU_RULES_DOMINOS;
                    } else if (i == 1) {
                        menu_state = MENU_RULES_TRIOMINOS;
                    } else if (i == 2) {
                        menu_state = MENU_MAIN;
                    }
                    break;
                }
            }
        } else if (menu_state == MENU_RULES_DOMINOS || menu_state == MENU_RULES_TRIOMINOS) {
            if (mouseX >= back_button.rect.x && mouseX <= back_button.rect.x + back_button.rect.w &&
                mouseY >= back_button.rect.y && mouseY <= back_button.rect.y + back_button.rect.h) {
                menu_state = MENU_RULES_SELECTION;
            }
        }
    }
}

void render_menu(Game* game) {
    SDL_Color white = {255, 255, 255, 255};
    const char* title_text = "Choisissez votre jeu";

    if (menu_state == MENU_RULES_SELECTION) {
        title_text = "Menu des Regles de Jeux";
    } else if (menu_state == MENU_RULES_DOMINOS) {
        title_text = "Regles de jeu Dominos";
    } else if (menu_state == MENU_RULES_TRIOMINOS) {
        title_text = "Regles de jeu Triominos";
    }

    SDL_Surface* title_surface = TTF_RenderText_Blended(font, title_text, white);
    SDL_Texture* title_texture = SDL_CreateTextureFromSurface(game->renderer, title_surface);
    SDL_Rect title_rect = {(game->window_width - title_surface->w) / 2, 50, title_surface->w, title_surface->h};
    SDL_RenderCopy(game->renderer, title_texture, NULL, &title_rect);
    SDL_FreeSurface(title_surface);
    SDL_DestroyTexture(title_texture);

if (menu_state == MENU_RULES_DOMINOS) {
    render_text(game->renderer, font, "1. Le jeu se joue avec 28 Dominos et de 2 a 4 joueurs.", 50, 150, white);
    render_text(game->renderer, font, "2. Les pieces de domino sont constituees de un nombre de 0 a 6 sur une moitie de domino ", 50, 200, white);
    render_text(game->renderer, font, "et sur lautre moitie egalement.", 50, 250, white);
    render_text(game->renderer, font, "3. Le but du jeu est de poser les Dominos les uns a la suite des autres sur une table en les combinant.", 50, 300, white);
    render_text(game->renderer, font, "4. Le joueur ayant le double le plus eleve (le double 6 donc) commence la partie de domino.", 50, 350, white);
    render_text(game->renderer, font, "5. Si personne ne possede ce domino, ce sera le joueur ayant le double le plus fort.", 50, 400, white);
    render_text(game->renderer, font, "6. Le joueur suivant doit a son tour poser un domino ayant le meme nombre de points sur au moins ", 50, 450, white);
     render_text(game->renderer, font, "un cote du domino precedemment pose.", 50, 500, white);
    
} else if (menu_state == MENU_RULES_TRIOMINOS) {
        render_text(game->renderer, font, "1. Le but du jeu est d obtenir un maximum de points en placant ses Triominos de facon strategique.", 50, 150, white);
    render_text(game->renderer, font, "2. Pour une partie a 2 joueurs, chaque joueur pioche 9 Triominos et pour une partie", 50, 200, white);
    render_text(game->renderer, font, "a 3 ou 4 joueurs, chacun pioche 7 Triominos", 50, 250, white);
    render_text(game->renderer, font, "3. chaque joueur pioche un Triominos. Celui qui obtient le plus fort total en additionnant ", 50, 300, white);
    render_text(game->renderer, font, "les chiffres de sa tuile devient le premier joueur. (en cas d egalite, piocher de nouveau)", 50, 350, white);
    render_text(game->renderer, font, "4. le premier joueur choisit l un de ses Triominos et le pose au milieu de la surface de jeu.", 50, 400, white);
    render_text(game->renderer, font, "5. Il marque un score correspondant au total des chiffres inscrits sur la tuile jouee ", 50, 450, white);
     render_text(game->renderer, font, "6. La partie se poursuit dans le sens des aiguilles d une montre.", 50, 500, white);
          render_text(game->renderer, font, "7. Le joueur dont c est le tour doit placer un Triominos a cote d une tuile deja posee.", 50, 550, white);

     render_text(game->renderer, font, "8. Pour que ce coup soit valide, ces Triominos doivent avoir un cote en commun, ", 50, 600, white);
     render_text(game->renderer, font, "ce qui signifie que les deux pointes doivent correspondre.", 50, 650, white);

}

    Button* active_buttons;
    int button_count;

    if (menu_state == MENU_MAIN) {
        active_buttons = main_buttons;
        button_count = 3;
    } else if (menu_state == MENU_RULES_SELECTION) {
        active_buttons = rules_buttons;
        button_count = 3;
    } else {
        active_buttons = &back_button;
        button_count = 1;
    }

    for (int i = 0; i < button_count; i++) {
        SDL_SetRenderDrawColor(game->renderer, 70, 70, 70, 255);
        SDL_RenderFillRect(game->renderer, &active_buttons[i].rect);
        SDL_SetRenderDrawColor(game->renderer, 200, 200, 200, 255);
        SDL_RenderDrawRect(game->renderer, &active_buttons[i].rect);

        SDL_Surface* text_surface = TTF_RenderText_Blended(font, active_buttons[i].text, white);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(game->renderer, text_surface);
        SDL_Rect text_rect = {active_buttons[i].rect.x + (BUTTON_WIDTH - text_surface->w) / 2, active_buttons[i].rect.y + (BUTTON_HEIGHT - text_surface->h) / 2, text_surface->w, text_surface->h};
        SDL_RenderCopy(game->renderer, text_texture, NULL, &text_rect);
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }
}
