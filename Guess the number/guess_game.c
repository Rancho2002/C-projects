#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int num, guess;
    srand(time(0));
    num = rand() % 100 + 1;
    char *name;
    printf("enter your name :\n");
    scanf("%s", name);
    // printf("%d",num);

    printf("Guess the number between 1 to 100\n");
    scanf("%d", &guess);

    int i;
    for (i = 1; guess != num; i++)
    {
        if (guess < num)
        {
            printf("Guess a larger number:\n");
            scanf("%d", &guess);
        }
        else if (guess > num)
        {
            printf("Guess a smaller number:\n");
            scanf("%d", &guess);
        }
        else
        {
            printf("Enter number pls:\n");
            scanf("%d", &guess);
        }
    }

    printf("Congratulations!!!! You guessed it right %s! party!\n", name);

    printf("Guesses used : %d", i);
    // int i=1;
    // do
    // {
    //     printf("Guess the number between 1 to 100:\n");
    //     scanf("%d",&guess);
    //     if(guess<num){
    //         printf("Larger number pls\n");
    //     }
    //     else if(guess>num){
    //         printf("Smaller number pls\n");
    //     }
    //     else{
    //         printf("Congratulations! You guessed it in %d attempts.",i);
    //     }
    //     i++;
    // } while (guess!=num);

    return 0;
}