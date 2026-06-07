#ifndef SCORES_H
#define SCORES_H

#define MAX_NAME_LEN 50
#define SCORE_FILE "scores.txt"

typedef struct {
  char player_name[MAX_NAME_LEN];
  int score;
} ScoreEntry;

void initScores(void); // Ensures the file exists
void saveScore(const char *name, int score);
void showLeaderboard(void);
void showPlayerHistory(const char *name);

#endif
