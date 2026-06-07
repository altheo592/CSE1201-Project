// Determines the question and category structure and declares all the functions in questions.c

#ifndef QUESTIONS_H
#define QUESTIONS_H

// The structure of a question with 4 choices and the correct answer letter defined
typedef struct {
    char question_text[250];
    char options[4][60];
    char correct_option;    /* 'A', 'B', 'C', or 'D' */
} Question;

// Defines the amount of questions a category can hold and displays the category name
typedef struct {
    char category_name[50];
    Question questions[5];
    int  question_count;
} Category;

void loadQuestions(Category categories[], int *count);//loads the array with all the questions
void printQuestion(Question q); // prints the questions and the four choices
void askQuestion(Question q); // prints the question and reads the player's answer

// runs a full game round and displays the final score
int  playRound(Category game_bank[], int num_categories,
               int category_choice, int difficulty,
               const char *player_name);

#endif
