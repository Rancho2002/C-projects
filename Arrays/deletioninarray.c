#include <stdio.h>
#include<stdlib.h>

int main()
{
    int a[100],m,k;
    printf("Enter the size of the array : ");
    scanf("%d",&m);
    printf("Enter the elements of the array : \n");
    for(int i=0;i<m;i++)
    {
        printf("a[%d] : ",i);
    scanf("%d",&a[i]);
    }
    printf("Enter the position of the item to be delete : \n");
    scanf("%d",&k);


    for(int i=0;i<m;i++)
    {
        if(i>=k)
        {
            a[i]=a[i+1];
        }
    }
     
     for(int i=0;i<m-1;i++)
     {
        printf("\na[%d] : %d",i,a[i]);
     }
    


    return 0;
}
