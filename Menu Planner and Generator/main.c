#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read a string from the user
void getInput(char *prompt, char *input, int maxLength) {
    printf("%s: ", prompt);
    fgets(input, maxLength, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove the newline character
}

int main() {
    char starter_food[100];
    char starter_plant[100];
    char starter_cooking_method[100];
    char starter_burned_word[100];

    char main_food[100];
    char main_plant[100];
    char main_cooking_method[100];
    char main_burned_word[100];

    char dessert_food[100];
    char dessert_plant[100];
    char dessert_cooking_method[100];
    char dessert_burned_word[100];

    printf("Welcome to the Menu Generator!\n");

    // Starter
    printf("\nStarter:\n");
    getInput("Enter a food for the starter", starter_food, sizeof(starter_food));
    getInput("Enter a type of plant for the starter", starter_plant, sizeof(starter_plant));
    getInput("Enter a method of cooking for the starter", starter_cooking_method, sizeof(starter_cooking_method));
    getInput("Enter a word to describe burned food", starter_burned_word, sizeof(starter_burned_word));

    // Main Course
    printf("\nMain Course:\n");
    getInput("Enter a food for the main course", main_food, sizeof(main_food));
    getInput("Enter a type of plant for the main course", main_plant, sizeof(main_plant));
    getInput("Enter a method of cooking for the main course", main_cooking_method, sizeof(main_cooking_method));
    getInput("Enter a word to describe burned food", main_burned_word, sizeof(main_burned_word));

    // Dessert
    printf("\nDessert:\n");
    getInput("Enter a food for the dessert", dessert_food, sizeof(dessert_food));
    getInput("Enter a type of plant for the dessert", dessert_plant, sizeof(dessert_plant));
    getInput("Enter a method of cooking for the dessert", dessert_cooking_method, sizeof(dessert_cooking_method));
    getInput("Enter a word to describe burned food", dessert_burned_word, sizeof(dessert_burned_word));

    // Additional features
    printf("1. Generate Shopping List\n");
    printf("2. Save Menu to File\n");
    printf("Enter your choice (1/2): ");
    
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        // Generate and display a shopping list
        printf("\nShopping List:\n");
        printf("---------------\n");
        printf("- %s for Starter\n", starter_food);
        printf("- %s for Main Course\n", main_food);
        printf("- %s for Dessert\n", dessert_food);
    } else if (choice == 2) {
        // Save the menu to a file
        FILE *file = fopen("menu.txt", "w");
        if (file != NULL) {
            fprintf(file, "MENU\n");
            fprintf(file, "-----\n");
            fprintf(file, "Starter:\n%s %s with %s %s 🥗\n\n", starter_cooking_method, starter_food, starter_burned_word, starter_plant);
            fprintf(file, "Main Course:\n%s %s with %s %s 🍛\n\n", main_cooking_method, main_food, main_burned_word, main_plant);
            fprintf(file, "Dessert:\n%s %s with %s %s 🍨\n\n", dessert_cooking_method, dessert_food, dessert_burned_word, dessert_plant);
            fclose(file);
            printf("\nMenu saved to 'menu.txt'.\n");
        } else {
            printf("\nFailed to save the menu. Please check permissions.\n");
        }
    } else {
        printf("\nInvalid choice.\n");
    }

    return 0;
}
