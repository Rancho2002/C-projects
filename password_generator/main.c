//password generator using c language:-
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char passwordType[1];

int generateRandomNumbers();

char password[512];

char passwordLength[];

void printPassword();

int main() {

    //using srand with time to update random function to generate random numbers with time

    srand(time(NULL));

    //A brief introduction

    printf("Welcome To Password Generator 2018\n");

    printf("You can generate any kind of password you would like to...\n");

    printf("Choose one of type below , you can choose both or triple too\n");

    printf("a) a to z \nb) A to Z \nc) 0 to 9 \nd) special characters only\ne) anything\nf) a & b\ng) a & c\n"
                   "h) a & d \ni) b & c \nj) b & d\nk) c & d\nl) a, b & c\nm) b, c & d\nn) a,c, &d "
                   "\no)a,b &d\np)a,b,c &d\n");

    printf("Enter any type given above(recommended == e)\n");

    //getting user input on what type of password the need..

    gets(passwordType);

    printf("Enter the password length\n");

    //prompting user for password length

    gets(passwordLength);

    //calling printPassword function to display the password selected by the user from the above options

    printf("How many passwords do you want??\n");

    char passwordTimes[1];

    gets(passwordTimes);

    int m = atoi(passwordTimes);

    printf("%d",m);

    while (m>0){

        printPassword();

        m--;

        _sleep(1000);

    }

    char isAgain[1];

    printf("Do you want to generate password again(y/n)\n");

    //asking user if he/she wants to generate password again, if yes then calling main function again

    gets(isAgain);

    if (isAgain[0] == 'y'){

        main();

    } else if (isAgain[0] == 'n'){

        printf("Thanks for using my password generator\n");

    } else{

        printf("Invalid input\n");

    }


    return 0;

}

// This function generating random numbers to generate password

int generateRandomNumbers(){

    int random;

    int r;

    // based on passwordType the user needs, generating random numbers

    switch (passwordType[0]){

        case 'a':

            random = (rand() % (122 + 1 - 97)) + 97;

            break;

        case 'b':

            random = (rand() % (90 + 1 - 65)) + 65;

            break;

        case 'c':

            random = (rand() % (57 + 1 - 48)) + 48;

            break;

        case 'd':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if (((r<=47) && (r>=33)) || ((r<=64) && (r>=58)) || ((r<=96) && (r>=91)) || ((r<=175) && (r>=123)) || ((r<=254) && (r>=178))){

                    random = r;

                    break;

                }

            }

            break;

        case 'e':

            random = (rand() % (126 + 1 - 33)) + 33;

            break;

        case 'f':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if (((r<=90) && (r>=65)) || ((r<=122) && (r>=97))){

                    random = r;

                    break;

                }

            }

            break;

        case 'g':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if (((r<=57) && (r>=48)) || ((r<=122) && (r>=97))){

                    random = r;

                    break;

                }

            }

            break;

        case 'h':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if (((r<=122) && (r>=97)) ||((r<=47) && (r>=33)) || ((r<=64) && (r>=58)) || ((r<=96) && (r>=91)) || ((r<=175) && (r>=123)) || ((r<=254) && (r>=178))){

                    random = r;

                    break;

                }

            }

            break;

        case 'i':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if (((r<=90) && (r>=65)) || ((r<=57) && (r>=48))){

                    random = r;

                    break;

                }

            }

            break;

        case 'j':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if (((r<=90) && (r>=65)) ||((r<=47) && (r>=33)) || ((r<=64) && (r>=58)) || ((r<=96) && (r>=91)) || ((r<=175) && (r>=123)) || ((r<=254) && (r>=178))){

                    random = r;

                    break;

                }

            }

            break;

        case 'k':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if (((r<=57) && (r>=48)) || ((r<=47) && (r>=33)) || ((r<=64) && (r>=58)) || ((r<=96) && (r>=91)) || ((r<=175) && (r>=123)) || ((r<=254) && (r>=178))){

                    random = r;

                    break;

                }

            }

            break;

        case 'l':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if(((r<=122) && (r>=97)) || ((r<=90) && (r>=65)) || ((r<=57) && (r>=48))){

                    random = r;

                    break;

                }

            }

            break;

        case 'm':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if(((r<=90) && (r>=65)) || ((r<=57) && (r>=48)) || ((r<=47) && (r>=33)) || ((r<=64) && (r>=58)) || ((r<=96) && (r>=91)) || ((r<=175) && (r>=123)) || ((r<=254) && (r>=178))){

                    random = r;

                    break;

                }

            }

            break;

        case 'n':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if(((r<=122) && (r>=97)) || ((r<=57) && (r>=48)) || ((r<=47) && (r>=33)) || ((r<=64) && (r>=58)) || ((r<=96) && (r>=91)) || ((r<=175) && (r>=123)) || ((r<=254) && (r>=178))){

                    random = r;

                    break;

                }

            }

            break;

        case 'o':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if(((r<=122) && (r>=97)) || ((r<=90) && (r>=65)) || ((r<=47) && (r>=33)) || ((r<=64) && (r>=58)) || ((r<=96) && (r>=91)) || ((r<=175) && (r>=123)) || ((r<=254) && (r>=178))){

                    random = r;

                    break;

                }

            }

            break;

        case 'p':

            while (1){

                r = (rand() % (256 + 1 - 0)) + 0;

                if(((r<=122) && (r>=97)) || ((r<=90) && (r>=65)) || ((r<=57) && (r>=48)) || ((r<=47) && (r>=33)) || ((r<=64) && (r>=58)) || ((r<=96) && (r>=91)) || ((r<=175) && (r>=123)) || ((r<=254) && (r>=178))){

                    random = r;

                    break;

                }

            }

            break;

        default:

            printf("Invalid Input so we are exiting you from program and starting again\n");

            main();

    }

    return random;

}

// Here is the main function which prints the password to the user

void printPassword(){

    int randomNumber;

    int k;

    //converting password length string to ineger to loop

    int length = atoi(passwordLength);

    //looping and generating random numbers and storing in password array

    for (k = 0; k < length; k++) {

        randomNumber = generateRandomNumbers();

        password[k] = randomNumber;

    }

    for (int j = 0; j < length+19; j++) {

        printf("=");

    }

    printf("\n");

    //Here Printing the password to the user

    printf("Your password is:  %s", password);

    printf("\n");

    for (int a = 0; a < length+19; a++) {

        printf("=");

    }

    printf("\n");

}
