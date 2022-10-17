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
    for(int i=0;i<m;i++)
    {
        for(int j=i+1;j<m;j++)
        {
          if(a[j]<a[i])
          {
            int temp = a[i];
            a[i]=a[j];
            a[j]=temp;
          }
        }
    }
    for(int i=0;i<m;i++)
     {
        printf("\na[%d] : %d",i,a[i]);
     }
    return 0;
}
