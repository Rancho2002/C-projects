/*************************************************************************
    > File Name: add_matrix.c
    > Author:YOUR_NAME
    > Mail:YOUR_MAIL_ADDRESS
    > Created Time: 2016年05月24日 星期二 15时59分43秒
 ************************************************************************/

#include <stdio.h>
#include "string.h"
#include "matrix.h"
#include <math.h>
#include "structure.h"

FILE *fp;

void add_present()
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\033[0;42m                                                                                 \033[0m\n");
	printf("*********************************************************************************\n");
	printf("*                                                                               *\n");
	printf("*                                ");
	printf("\033[0;31m 输入或导入矩阵 \033[0m");
	printf("                               *\n");
	printf("*                                                                               *\n");
	printf("*********************************************************************************\n");
	printf("*                                                                               *\n");
	printf("*                             请输入您想选择的操作：                            *\n");
	printf("*                               1.从键盘中输入                                  *\n");
	printf("*                               2.从文件中导入                                  *\n");
	printf("*                               3.退出矩阵的导入                                *\n");
	printf("*                                                                               *\n");
	printf("*********************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("您的选择是:");
	return;
}

void Input()
{
	printf("\n");
	
	int i;
	for(i=0;i<Volume_s;i++)
	{
		if(!(store[i].col>0&&store[i].row>0))
		{
//			printf("This is the %dth matrix\n",i);
//			absorb Enter
			char absorb;
			scanf("%c",&absorb);

			printf("请用一个字母来代表将要输入的矩阵：\n");
			char name;
			scanf("%c",&name);
			store[i].name=name;

			printf("请输入矩阵的行数与列数：\n");
			int row,col;
			scanf("%d",&row);
			scanf("%d",&col);
			store[i].row=row;
			store[i].col=col;

			printf("请输入矩阵的值：\n");
			float value;
			int r,c;
			for(r=0;r<row;r++)
			{
				for(c=0;c<col;c++)
				{
					scanf("%f",&value);
					store[i].value[r][c]=value;
				}
			}

			printf("\033[1;32m输入成功!\033[0m\n");
			printf("\n\n\n\n\n\n\n\n");
			printf("                         \033[1;33m  输入的矩阵为:   \033[0m \n");
			printf("                                  \033[1;35m%c=\n",store[i].name);
			
			int a,b;
			for(a=0;a<store[i].row;a++)
			{
				printf("                                  ");
				for(b=0;b<store[i].col;b++)
				{
					int n_value=(int)store[i].value[a][b];
					if(fabs(n_value-store[i].value[a][b])<1e-4)
					{
						printf("%d ",n_value);
					}
					else
						printf("%f ",store[i].value[a][b]);
				}
				printf("\n");
			}
			printf("\033[0m");
			break;
		}
	}
	printf("\n\n\n\n\n\n\n\n\n\n");
	sleep(2);
}


void Entry_all(char *adress)
{
	char name;
	int row;
	int col;
	float value;

	printf("\n\n");
	int i;
	for(i=0;i<Volume_s&&!feof(fp);i++)
	{
		if(!(store[i].col>0&&store[i].row>0))
		{
			fscanf(fp,"%c %d %d",&name,&row,&col);	

			if(feof(fp))
			{
				printf("\n\n\n\n\n\n");
				sleep(2);
				return;
			}

			printf("\033[1;32m                                正在导入矩阵 %c\033[0m\n",name);
			store[i].name=name;
//			printf("the name is: %c\n",name);

//			fscanf(fp,"%d",&row);
//			fscanf(fp,"%d",&col);
			store[i].row=row;
			store[i].col=col;
//			printf("the row is: %d\n",row);
//			printf("the col is: %d\n",col);

			int n,m;
			for(n=0;n<row;n++)
			{
				for(m=0;m<col;m++)
				{
					fscanf(fp,"%f",&value);
					store[i].value[n][m]=value;
//					printf("the value is: %f\n",value);
				}
			}		

			char absorb;
			fscanf(fp,"%c",&absorb);
//			printf("%c\n",absorb);
		}

	}

	printf("矩阵全部导入完毕！\n");
	sleep(2);
}


void Entry_one(char *adress)
{
	fp=fopen(adress,"r");
	if(fp==NULL)
	{
		printf("打开文件 %s 失败!\n",adress);
		return;
	}

	show(adress);

	printf("请输入您想从中导入的矩阵名：\n");
	char name;
	char absorb;
	scanf("%c",&absorb);
	scanf("%c",&name);

	char ch;
	fscanf(fp,"%c",&ch);
	while(!feof(fp))
	{
		if(ch==name)
		{
			int i;
			for(i=0;i<Volume_s;i++)
			{
				if(!(store[i].row>0&&store[i].col>0))
				{
//					printf("this is the %dth matrix\n",i);
					store[i].name=name;
					int row;
					int col;
					fscanf(fp,"%d",&row);
					fscanf(fp,"%d",&col);
					store[i].row=row;
					store[i].col=col;
//					printf("row is %d\n",row);
//					printf("col is %d\n",col);
					
					int r,c;
					float value;
					for(r=0;r<row;r++)
					{
						for(c=0;c<col;c++)
						{
							fscanf(fp,"%f",&value);
							store[i].value[r][c]=value;
						}
					}
					break;
				}
			}
			printf("\n");
			printf(" \033[1;32m从中导入成功!\033[0m\n\n\n\n\n\n");
			sleep(2);
			return;
		}
		fscanf(fp,"%c",&ch);
	}
	printf("\033[1;31m该文件夹中没有该矩阵!\033[0m\n");
	sleep(2);
	return;
}


void Import()
{

	printf("请输入选择的文件名:");
	char adress[200];
	scanf("%s",&adress);

	printf("我们得到你输入的地址是: \033[1;33m%s\033[0m\n",adress);
	fp=fopen(adress,"r");
	if(fp==NULL)
	{
		printf("\033[1;31m打开文件:%s 失败!\033[0m\n",adress);
		printf("\n");
		sleep(2);
		return;
	}
	printf("\033[1;32m打开文件成功!\033[0m\n");
	printf("\n");

	printf("\033[1;34m*********************************************************************************\033[0m\n");
	printf("请输入您要选择的从文件导入的方式:\n");
	printf("   1.导入全部矩阵\n");
	printf("   2.从中导入选中的矩阵\n");
	printf("   3.退出矩阵的导入\n");
	printf("\033[1;34m*********************************************************************************\033[0m\n");
	printf("\n");
	printf("您的选择: ");
	
	int choice1;
	scanf("%d",&choice1);

	switch(choice1)
	{
		case 1:
			{
				Entry_all(adress);
				fclose(fp);
				break;
			}
		case 2:
			{
				Entry_one(adress);
				fclose(fp);
				break;
			}
		case 3:
			{
				fclose(fp);
				return;
			}
		default:
			{
				printf("你的输入无效! 请再次输入.\n");
				sleep(2);
				return;
			}
	}
}
	
	
void add_matrix()
{
	do
	{
		add_present();
		int choice;
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				{
					Input();
					break;
				}
			case 2:
				{
					Import();
					break;
				}
			case 3:
				{
					return;
				}
			default:
				{
					printf("\n");
					printf("你的输入无效! 请再次输入.\n");
					sleep(2);
					break;
				}
		}
	}while(1);
}

void show(char *adress)
{
	FILE* fp2=fopen(adress,"r");
	printf("\033[1;32m目前文件中拥有的矩阵有：\033[0m\n");
	char c;
	do
	{
		fscanf(fp2,"%c",&c);
		if(c>='A'&&c<='Z')
		{
			printf("%c ",c);
		}
	}while(!feof(fp2));
	printf("\n");
	fp2=NULL;
	return;
}
