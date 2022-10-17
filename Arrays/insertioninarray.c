#include <stdio.h>
#include<stdlib.h>

int main()
{
    int a[100],m,k,item;
    printf("Enter the size of the array : ");
    scanf("%d",&m);
    printf("Enter the elements of the array : \n");
    for(int i=0;i<m;i++)
    {
        printf("a[%d] : ",i);
    scanf("%d",&a[i]);
    }
    printf("Enter the position of the item to be insert : \n");
    scanf("%d",&k);

    printf("Enter the item to be insert: \n");
    scanf("%d",&item);

    int j=m;

    for(int i=0;i<m;i++)
    {
        if(i>=k)
        {
            a[i+1]=a[i];
        }
    }

    a[k]=item ;

    for(int i=0;i<=m;i++)
    {
        printf("\na[%d] :",i);
        printf(" %d ",a[i]);
    
    }

    return 0;
}
