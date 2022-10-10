#include <stdio.h>

int main(){
    FILE *fptr1,*fptr2;
    fptr1=fopen("index.html","r");
    char text=fgetc(fptr1);
    if(fptr1==NULL)
        printf("Cannot Open Target File.");
    else
    {
        fptr2=fopen("compress.txt","w");
        while(text!=EOF){
            fptr2=fopen("compress.txt","a");
            if(text==' ' || text=='\n')
            {
                text=fgetc(fptr1);
                continue;
            }    
            else
                fputc(text,fptr2);
            text=fgetc(fptr1);
        }
    }
    return 0;
}