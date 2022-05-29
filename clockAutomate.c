#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void delay(int ss)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * ss;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
int main()
{
    int hh, mm, ss;
    printf("Enter current time in hour-minute-second format separeted by spaces : ");
    scanf("%d%d%d", &hh, &mm, &ss);
    while (1)
    {
        delay(1);
        ss++;
        if (ss == 60)
        {
            ss = 0;
            ss++;
            mm++;
            system("cls");
        }
        if (mm == 60)
        {
            mm = 0;
            hh++;
            system("cls");
        }

        if (hh == 24)
        {
            hh = 0;
            system("cls");
        }
        printf("%d : %d : %d", hh, mm, ss);
        printf("\r");
    }

    return 0;
}
