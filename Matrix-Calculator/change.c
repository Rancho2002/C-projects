/*************************************************************************
    > File Name: Change.c
    > Author:YOUR_NAME
    > Mail:YOUR_MAIL_ADDRESS
    > Created Time: 2016年06月08日 星期三 18时39分35秒
 ************************************************************************/

#include <stdio.h>
#include <math.h>
#include "structure.h"
#include "matrix.h"

int good(char newname)
{
	int i;
	for(i=0;store[i].row>0;i++)
	{
		if(store[i].name==newname)
		{
			return 0;
		}
	}
	return 1;
}

void changename(char name,char newname)
{
	int s;
	for(s=0;store[s].row>0;s++)
	{
		if(store[s].name==name)
		{
			store[s].name=newname;
		}
	}
	return;
}

void changevalue(char name)
{
	printf("\n请输入修改后矩阵行数与列数:\n");
	int row,col;
	scanf("%d",&row);
	scanf("%d",&col);

	int i;
	for(i=0;store[i].name!=name;i++);

	store[i].row=row;
	store[i].col=col;
	int r,c;
	for(r=0;r<10;r++)
	{
		for(c=0;c<10;c++)
			store[i].value[r][c]=0;
	}


	printf("请输入修改后矩阵的值:\n");
	for(r=0;r<row;r++)
	{
		for(c=0;c<col;c++)
		{
			scanf("%f",&store[i].value[r][c]);
//			printf("r=%d,c=%d,row=%d,col=%d\n",r,c,row,col);
		}
	}
	return;
}

void change()
{
	printf("\n请输入您想修改的矩阵名: ");
	char name;
	char absorb;
	scanf("%c",&absorb);
	scanf("%c",&name);

	int i;
	do
	{
		printf("\033[1;34m*********************************************************************************\033[0m\n");
		printf("请输入您的选择：\n");
		printf("	1.修改矩阵名称\n");
		printf("	2.修改矩阵行数列数或值\n");
		printf("\033[1;34m*********************************************************************************\033[0m\n");
		int choice;
		char absorb;
		printf("您的选择是: ");
		scanf("%c",&absorb);
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				{
					char newname;
					char absorb1;
					printf("请输入新的名称(一个大写字母): \n");
					scanf("%c",&absorb1);
					do
					{
						scanf("%c",&newname);
					}while(!(newname>='A'&&newname<='Z'));

					if(1==good(newname))
					{
						changename(name,newname);
						printf("\033[1;32m修改成功！\033[0m\n");
						printf("\n\n\n\n\n");
						sleep(2);
						return;
					}
					else 
					{
						printf("\033[1;33m已有该矩阵，无法修改！\033[0m\n");
						break;
					}
				}
			case 2:
				{
					changevalue(name);
					printf("\033[1;32m修改成功！\033[0m\n");
					sleep(2);
					return;
				}
			default:
				{
					printf("\033[1;33m输入无效，请重新输入！\033[0m\n");
					break;
				}
		}
	}while(1);
	return;
}

