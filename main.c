// This file handles how the entire application functions; controls the application loop,
// menu and the questions and scoring modules
#include <stdio.h>     // neccesary for printf, scanf and the like
#include <string.h>    // neccesary for all teh sting functions 
#include "questions.h" // loads the question structure file
#include "scores.h"    // loads the leaderbaord functions

// Logic to clear anything leftover in the input buffer after a scanf 
static void flushInput(void) {
    int c; 
    while ((c = getchar()) != '\n' && c != EOF);
}

// Prints the game's name
static void printHeader(void) { 
    printf("\n");
    printf("  ============================================\n");
    printf("     What Yuh Know Bout Guyana?\n");
    printf("     CSE1201 Group Project\n");
    printf("  ============================================\n");
}

// Selecting the category of question before the game starts
static int chooseCategory(Category game_bank[], int num_categories) {
    printf("\n  Select a category:\n"); 
    printf("    0. All Categories (random mix)\n");
    for (int i = 0; i < num_categories; i++) 
        printf("    %d. %s\n", i + 1, game_bank[i].category_name); 
    printf("  Enter choice [0-%d]: ", num_categories); 

    int choice;
    if (scanf("%d", &choice) != 1 || choice < 0 || choice > num_categories)
        choice = 0;
    flushInput();
    return choice;
}

// Selecting diffculty level of the questions
static int chooseDifficulty(void) {
    printf("\n  Select difficulty:\n");
    printf("    1. Easy   (5 lives, 10 pts per question)\n");
    printf("    2. Medium (3 lives, 20 pts per question)\n");
    printf("    3. Hard   (1 life,  30 pts per question)\n");
    printf("  Enter choice [1-3]: ");

    int choice;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 3)
        choice = 1; // defaults to easy if something weird is typed
    flushInput();
    return choice;
}

// Main
int main(void) {

    Category game_bank[10];
    int num_categories = 0;

    loadQuestions(game_bank, &num_categories);  
    initScores();                                // loads the save scores from txt file

    // collects the player's name
    char player_name[MAX_NAME_LEN];
    printHeader();
    printf("  Enter your name: ");
    if (fgets(player_name, MAX_NAME_LEN, stdin) == NULL)
        strcpy(player_name, "Player");

    player_name[strcspn(player_name, "\n")] = '\0'; // fgets leaves a new line character so this removed it 

    if (strlen(player_name) == 0)
        strcpy(player_name, "Player");

    // Main menu loop that runs until game is exited
    int running = 1; // this handles the loop, 1 is keep going and 0 is quit
    while (running) { // shows menu until exited
        printHeader();
        printf("  Hello, %s!\n\n", player_name);
        printf("  1. Play Game\n");
        printf("  2. Leaderboard\n");
        printf("  3. Score History\n");
        printf("  4. Change Player\n");
        printf("  5. Quit\n");
        printf("  ============================================\n");
        printf("  Enter your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) { flushInput(); continue; }  // if the input fails, clear the buffer and show menu again
        flushInput(); // clears the newline

        if (choice == 1) {
            int cat  = chooseCategory(game_bank, num_categories);
            int diff = chooseDifficulty();
            playRound(game_bank, num_categories, cat, diff, player_name);

            printf("\n  Press ENTER to return to menu...");
            getchar();

        } else if (choice == 2) {
            showLeaderboard();
            printf("\n  Press ENTER to continue...");
            getchar();

        } else if (choice == 3) {
            showPlayerHistory(player_name);
            printf("\n  Press ENTER to continue...");
            getchar();

        } else if (choice == 4) {
            printf("  Enter new player name: ");
            if (fgets(player_name, MAX_NAME_LEN, stdin) == NULL)
                strcpy(player_name, "Player");
            player_name[strcspn(player_name, "\n")] = '\0';
            if (strlen(player_name) == 0)
                strcpy(player_name, "Player");

        } else if (choice == 5) {
            running = 0;

        } else {
            printf("  Invalid choice, please try again.\n");
        }
    }

    printf("\n  Thanks for playing, %s! Goodbye!\n\n", player_name);
    return 0;
}
