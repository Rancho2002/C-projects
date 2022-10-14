#include<stdio.h>
#include<stdlib.h>    // to use system() method

int main()
{
    printf("\n\n\t\tStudytonight - Best place to learn\n\n\n");

    char ch;
    
    printf("Do you want to shutdown your pc now (y/n)?");
    scanf("%c", &ch);

    if(ch == 'y'|| ch == 'Y')
    {   /*
            /s is used to order the compiler 
            to shutdown the PC
        */
        system("C:\\WINDOWS\\System32\\shutdown /s");
    }

    printf("\n\n\t\t\tCoding is Fun !\n\n\n");
    return 0;
}
