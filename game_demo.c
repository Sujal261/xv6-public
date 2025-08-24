#include "types.h"
#include "stat.h"
#include "user.h"

void
number_guessing_game()
{
    msgbox("Starting Number Guessing Game!");
    
    int secret = (random() % 100) + 1;  // 1-100
    int guess, attempts = 0;
    char message[100];
    
    printf("\n=== Number Guessing Game ===\n");
    printf("I'm thinking of a number between 1 and 100!\n");
    printf("(In a real system, you'd input guesses. Here's a demo with random guesses)\n\n");
    
    // Simulate guessing (since xv6 doesn't have easy input)
    for(attempts = 1; attempts <= 10; attempts++) {
        guess = (random() % 100) + 1;
        printf("Attempt %d: Guessing %d... ", attempts, guess);
        
        if(guess == secret) {
            printf("🎉 CORRECT!\n");
            strcpy(message, "Congratulations! You won the game!");
            msgbox(message);
            return;
        } else if(guess < secret) {
            printf("Too low!\n");
        } else {
            printf("Too high!\n");
        }
        
        sleep(1);
    }
    
    printf("\nGame Over! The number was %d\n", secret);
    strcpy(message, "Better luck next time!");
    msgbox(message);
}

void
dice_game()
{
    msgbox("Starting Dice Rolling Game!");
    
    printf("\n=== Dice Rolling Game ===\n");
    printf("Rolling two dice 5 times...\n\n");
    
    int total_score = 0;
    char message[100];
    
    for(int i = 1; i <= 5; i++) {
        int die1 = (random() % 6) + 1;
        int die2 = (random() % 6) + 1;
        int sum = die1 + die2;
        total_score += sum;
        
        printf("Roll %d: [%d] + [%d] = %d", i, die1, die2, sum);
        
        if(sum == 7) {
            printf(" - Lucky 7! 🍀");
        } else if(sum == 12) {
            printf(" - Boxcars! 🎲🎲");
        } else if(sum == 2) {
            printf(" - Snake eyes! 🐍");
        }
        printf("\n");
        
        sleep(1);
    }
    
    printf("\nTotal score: %d points!\n", total_score);
    
    if(total_score >= 30) {
        strcpy(message, "Excellent rolling! You're on fire! 🔥");
    } else if(total_score >= 20) {
        strcpy(message, "Good job! Nice rolling! 👍");
    } else {
        strcpy(message, "Better luck next time! 🎲");
    }
    
    msgbox(message);
}

int
main(int argc, char *argv[])
{
    printf("=== XV6 Game Demo Using Random & MsgBox ===\n");
    
    msgbox("Welcome to the XV6 Game Demo!");
    
    number_guessing_game();
    sleep(2);
    
    dice_game();
    
    msgbox("Thanks for playing! Game demo complete!");
    
    exit(0);
}