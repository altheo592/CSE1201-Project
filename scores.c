// Handles saving scores, loading the leaderboard and showing player history
// scores are saved to a plain text file so they persist between sessions

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scores.h"

// creates the scores file if it doesnt already exist on first run
void initScores(void) {
    FILE *f = fopen(SCORE_FILE, "a");
    if (f) {
        fclose(f); // just opens and closes to make sure the file is there
    }
}

// appends a new name and score to the scores file
void saveScore(const char *name, int score) {
    FILE *f = fopen(SCORE_FILE, "a"); // "a" = append so old scores arent deleted
    if (!f) {
        printf("  Warning: could not save score.\n");
        return;
    }
    fprintf(f, "%s|%d\n", name, score);
    fclose(f);
}

// sorts scores highest to lowest using bubble sort
static void sortScores(ScoreEntry entries[], int count) {
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (entries[j].score < entries[j + 1].score) {
                // swap
                ScoreEntry temp = entries[j];
                entries[j]      = entries[j + 1];
                entries[j + 1]  = temp;
            }
        }
    }
}

// reads all scores from file, sorts them, prints top 10
void showLeaderboard(void) {
    FILE *f = fopen(SCORE_FILE, "r");
    if (!f) {
        printf("\n  No scores saved yet.\n");
        return;
    }

    ScoreEntry entries[100];
    int count = 0;

    // read each line into the entries array
    while (count < 100 && fscanf(f, "%49[^|]|%d", entries[count].player_name, &entries[count].score) == 2) {
        count++;
    }
    fclose(f);

    sortScores(entries, count);

    printf("\n  =====================================================\n");
    printf("              TOP 10 LEADERBOARD\n");
    printf("  =====================================================\n");

    if (count == 0) {
        printf("  No scores yet, be the first!\n");
    } else {
        int i;
        int show = count < 10 ? count : 10; // show at most 10
        for (i = 0; i < show; i++) {
            printf("  %2d. %-20s %d\n", i + 1, entries[i].player_name, entries[i].score);
        }
    }
    printf("  =====================================================\n");
}

// shows the last 5 scores for a specific player
void showPlayerHistory(const char *name) {
    FILE *f = fopen(SCORE_FILE, "r");
    if (!f) {
        printf("\n  No score history found.\n");
        return;
    }

    char read_name[MAX_NAME_LEN];
    int  read_score;

    // collect all scores for this player into an array
    int history[100];
    int hcount = 0;

    /*while (fscanf(f, "%49s %d", read_name, &read_score) == 2) {   ← read each line from the file
    if (strcmp(read_name, name) == 0) {   ← check if this line belongs to this player
        history[hcount++] = read_score;   ← if so, add the score to their history
        replaced with below because scores were not displaying in terminal
    */

    while (hcount < 100 && fscanf(f, "%49[^|]|%d", read_name, &read_score) == 2) {
        if (strcmp(read_name, name) == 0) {
            history[hcount++] = read_score;
        }
    }
    fclose(f);

    printf("\n  =====================================================\n");
    printf("  Score History for: %s\n", name);
    printf("  =====================================================\n");

    if (hcount == 0) {
        printf("  No scores yet for %s, go play!\n", name);
    } else {
        // only show the 5 most recent scores (last 5 entries in the file)
        int start = hcount > 5 ? hcount - 5 : 0;
        int i;
        for (i = start; i < hcount; i++) {
            printf("  %d.  %d pts\n", i - start + 1, history[i]);
        }
    }
    printf("  =====================================================\n");
}