#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gameValue(char comp, char me)
{
    // 1st person can chose 3 items in 3 any ways
    // 2nd person also pick any items in 3 ways...
    // so it 3x3 = 9 ways! that mean 9 outcomes in this game!

    if (comp == me)
    {
        return 0;
    } // ss,ww,gg

    // snake-
    else if (me == 's' && comp == 'w')
    {
        return 1;
    }

    else if (me == 's' && comp == 'g')
    {
        return -1;
    }

    // water-

    else if (me == 'w' && comp == 's')
    {
        return -1;
    }
    else if (me == 'w' && comp == 'g')
    {
        return 1;
    }

    // gun-

    else if (me == 'g' && comp == 'w')
    {
        return -1;
    }
    else if (me == 'g' && comp == 's')
    {
        return 1;
    }
}

int main()
{
    int num;
    srand(time(0));
    num = rand() % 100 + 1;

    char comp, me;

    if (num < 33)
    {
        comp = 's';
    }
    else if (num > 33 && num < 66)
    {
        comp = 'g';
    }
    else
    {
        comp = 'w';
    }
label:
    printf("Enter 's' for snake, 'g' for gun & 'w' for water : ");
    fflush(stdin);
    scanf("%c", &me);

    int result = gameValue(comp, me);

    if (result == 1)
    {
        printf("Congratulations!!! You Won!\n");
    }
    else if (result == -1)
    {
        printf("Alas!!! You Lost!\n");
    }
    else if (result == 0)
    {
        printf("It's a tie.\n");
    }
    else
    {
        goto label;
    }
    printf("You chose : %c\n", me);
    printf("Computer chose : %c\n", comp);
    return 0;
}
