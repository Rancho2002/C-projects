#include <stdio.h>

int main(){
    int range,num;
    printf("Enter the number of which the multiplication table you want : ");
    scanf("%d",&num);
    printf("Enter the range of the multiplication table e.g. 10 : ");
    scanf("%d",&range);
    FILE *fptr;
    char *s="table.txt";
    fptr=fopen(s,"w");
    for(int i=1;i<=range;i++){
        fprintf(fptr,"%d X %d = %d\n",num,i,num*i);
    }
    printf("\nMultiplication Table of %d generated successfully.\n",num);
    fclose(fptr);
    return 0;
}