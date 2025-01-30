#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_score.h"

void save_scores_to_file(const char* game_type, PlayerScore* players, int num_players) {
    FILE* file = fopen("scores.txt", "a+");  
    if (!file) {
        printf("Error opening scores.txt\n");
        return;
    }

    int last_game_number = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "JEU", 3) == 0) {  
            int game_number;
            if (sscanf(line, "JEU %*s %d", &game_number) == 1) {
                last_game_number = game_number;  
            }
        }
    }

    int new_game_number = last_game_number + 1;
    fprintf(file, "JEU %s %d\n", game_type, new_game_number);
    
    for (int i = 0; i < num_players; i++) {
        fprintf(file, "%s: %d\n", players[i].username, players[i].score);
    }
    fprintf(file, "----------------------\n");
    fclose(file);
}



