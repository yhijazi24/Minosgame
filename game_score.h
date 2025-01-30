#ifndef GAME_SCORE_H
#define GAME_SCORE_H

typedef struct {
    char username[50];
    int score;
} PlayerScore;

void save_scores_to_file(const char* game_type, PlayerScore* players, int num_players);

#endif
