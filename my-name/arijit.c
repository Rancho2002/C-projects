#include <stdio.h>

int main(){
    int row,col,i,j,space;
    row=6,col=6;
    for(i=1;i<=row;i++){

        //! A
        for(j=1;j<=col;j++){
            if(i==1 || j==1 || j==col|| i==row/2)
            printf("* ");
            else
            printf("  ");
        }

        for(j=1;j<=col;j++){
            printf(" ");
        }


        //! R
        for(j=1;j<=col;j++){
            if(i==1 || j==1 || i==row/2 || (j==col && i<=row/2) || (i==4 && j==4) || (i==5 && j==5) || (i==col && j==row))
            printf("* ");
            else
            printf("  ");
        }

        for(j=1;j<=col;j++){
            printf(" ");
        }

        //! I
        for(j=1;j<=col;j++){
            if(i==1 || j==col/2 || i==row)
            printf("* ");
            else
            printf("  ");
        }
        for(j=1;j<=col;j++){
            printf(" ");
        }

        //! J
        for(j=1;j<=col;j++){
            if(i==1 || j==col || (j>=col/2-1 && i==row) || (i>row/2 && j==col/2-1))
            printf("* ");
            else
            printf("  ");
        }

         for(j=1;j<=col;j++){
            printf(" ");
        }

        //! I
        for(j=1;j<=col;j++){
            if(i==1 || j==col/2 || i==row)
            printf("* ");
            else
            printf("  ");
        }

         for(j=1;j<=col;j++){
            printf(" ");
        }

        //! T
        for(j=1;j<=col;j++){
            if(j==col/2 || i==1)
            printf("* ");
            else
            printf("  ");
        }
        printf("\n");
    }

return 0;
}