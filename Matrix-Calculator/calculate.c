/*************************************************************************
    > File Name: caculate.c
    > Author:YOUR_NAME
    > Mail:YOUR_MAIL_ADDRESS
    > Created Time: 2016年05月24日 星期二 16时00分29秒
 ************************************************************************/

#include <stdio.h>
#include "string.h"
#include "matrix.h"
#include "structure.h"
#include "math.h"
#define adress "record.txt"
//extern int legal(char *castr);

FILE *fp1;

void transist()
{
	int i;
	for(i=0;store[i].row>0;i++)
	{
		count[i].name=store[i].name;
		count[i].row=store[i].row;
		count[i].col=store[i].col;
		int r,c;
		for(r=0;r<store[i].row;r++)
		{
			for(c=0;c<store[i].col;c++)
			{
				count[i].value[r][c]=store[i].value[r][c];	
			}
		}
	}
}

void clear()
{
	int i;
	for(i=0;count[i].row>0;i++)
	{
		count[i].name='\0';
		int row=count[i].row;
		int col=count[i].col;
		count[i].row=0;
		count[i].col=0;
		int r,c;
		for(r=0;r<row;r++)
		{
			for(c=0;c<col;c++)
			{
				count[i].value[r][c]=0;
			}
		}
	}

}


void fenshu(float n,int *up,int *down)
{
	int mul=1;
	float result;
	int res;
	do
	{
		mul++;
		result=mul*n;
		res=(int)result;
	}while(fabs(result-res)>1e-3&&mul<20);
	
	int common=1;
	int i;
	for(i=2;i<=fabs(mul)&&i<=fabs(res);i++)
	{
		if(mul%i==0&&res%i==0)
		{
			common=i;
		}
	}

	*up=res/common;
	*down=mul/common;
}

void present(char ch)
{
	printf("\n\n");
	int i;
	for(i=0;count[i].row>0;i++)
	{
		if(count[i].name==ch)
		{
			printf("                             \033[1;31m  结果 :    \033[0m\n\n");
			fputs("计算结果为：\n",fp1);
			int row=count[i].row;
			int col=count[i].col;
			int r,c;
			for(r=0;r<row;r++)
			{
				printf("                               ");
				fputs("			",fp1);
				for(c=0;c<col;c++)
				{
					int a=(int)count[i].value[r][c];
					if(fabs(a-count[i].value[r][c])<1e-3)
					{
						printf("\033[1;33m%d\033[0m ",a);
						fprintf(fp1,"%d ",a);
					}
					else if(fabs(a+1-count[i].value[r][c])<1e-3)
					{
						printf("\033[1;33m%d\033[0m ",a+1);
						fprintf(fp1,"%d ",a+1);
					}
					else if(fabs(a+0.5-count[i].value[r][c])<1e-3||fabs(a-0.5-count[i].value[r][c])<1e-3)						
					{
						int w=a*2+1;
						printf("\033[1;33m%d/2\033[0m ",w);
						fprintf(fp1,"%d/2 ",w);
					}
					else
					{
						int up,down;
						fenshu(count[i].value[r][c],&up,&down);
						printf("\033[1;33m%d/%d \033[0m",up,down);
						fprintf(fp1,"%d/",up);
						fprintf(fp1,"%d ",down);
					}
				}
				printf("\n");
				fputs("\n\n",fp1);
			}
			break;
		}
	}
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\033[44m按 'Enter' 键退出帮助.                                                               \033[0m");
	char absorb;
	char choice;
	scanf("%c",&absorb);
	scanf("%c",&choice);
	if('\n'==choice)
	{
		;
	}

}

float Fun(int n1,float a[10][10])
{
	int i_1,j_1,c;            //c为数组b的行
	float b[10][10];            //用于存放余子式
	int p=0,q=0;
	double sum=0;
	if(n1==1) 
	{
		return a[0][0];
	}

	for(i_1=0;i_1<n1;i_1++)
	{
		for(c=0;c<n1-1;c++)
		{
			if(c<i_1) 
				p=0;
			else 
				p=1;
			for(j_1=0;j_1<n1-1;j_1++)
			{
				b[c][j_1]=a[c+p][j_1+1];
			}
		 }
		if(i_1%2==0) 
			q=1;
		else
			q=(-1);
		sum=sum+a[i_1][0]*q*Fun(n1-1,b);
	}
	return sum;
}

void present1(char ch)
{
	int i;
	for(i=0;count[i].name!=ch;i++);
	int row=count[i].row;
	int col=count[i].col;
	if(row!=col)
	{
		printf("\033[1;31m结果行数与列数不相等，不能计算行列式！\033[0m\n");
		sleep(2);
		fputs("结果行数与列数不相等，不能计算行列式！\n\n",fp1);
		return;
	}

	else
	{
		float res=Fun(row,count[i].value);
		printf("行列式的值为=\033[1;33m%.2lf\033[0m\n",res);
		sleep(2);
		fputs("行列式的值为=",fp1);
		char buf[20]="\0";
		sprintf(buf,"%f",res);
		fputs(buf,fp1);
		fputs("\n\n",fp1);
		return;
	}
}

int hang(char *castr)
{
	int i=0;
	int lenth=strlen(castr);
	for(;i<lenth;i++)
	{
		if(castr[i]=='!')
			return 1;
	}
	return 0;
}

void calculate()
{
	fp1=fopen(adress,"a");
	printf("\n");
	printf("\033[42m\n");
	printf(" 你可以使用:\n");
	printf("     字母: A-Z  \n");
	printf("     操作符：'+'    '-'    '*'    '/'   '()'    '|1'    '!'    '^'   '$'\033[0m\n\n");
	printf("请输入表达式：\n");
	char castr[100];
	scanf("%s",castr);
//	printf("%s\n",castr);
	if(1==legal(castr))
	{
		char biaodashi[100]="\0";
		strcat(biaodashi,"计算表达式为：");
		strcat(biaodashi,castr);
		fputs(biaodashi,fp1);
		fputs("\n",fp1);

		transist();
		char result,result1;
		if(0==hang(castr))
			result=jisuan(castr);
		else
		{
			int lenth=strlen(castr);
			char castr1[50];
			strcpy(castr1,castr);
//			printf("castr1=%s\n",castr1);
			int pointer=0;
			for(;pointer<lenth-1;pointer++)
				castr1[pointer]=castr1[pointer+1];
			castr1[lenth-1]='\0';
			result1=jisuan(castr1);
//			printf("result1=%c\n",result1);
		}

		if('?'==result||'?'==result1)
		{
			return;
		}
		
		
		if(0==hang(castr))
			present(result);
		else 
		{
//			printf("result1=%c\n",result1);
			present1(result1);
		}
		clear();
	}

	else
	{
		printf("\033[1;31m表达式输入有误!!!\033[0m\n");
		sleep(2);
	}

	fclose(fp1);
	return;
}

int equal(char *castr,int lenth)
{
	int numl=0;
	int numr=0;
	int i;
	for(i=0;i<lenth;i++)
	{
		if(castr[i]=='(')
			numl++;
		if(castr[i]==')')
			numr++;
	}
//	printf("numl=%d  numr=%d\n",numl,numr);

	if(numl>numr)
		return -1;
	else if(numl<numr)
		return 1;
	else 
		return 0;
}

int legal(char *castr)
{
	int lenth;
	lenth=strlen(castr);
//	printf("lenth is %d\n",lenth);
	int i;
	for(i=0;i<lenth;i++)
	{
//		if(castr[i]>='a'&&castr[i]<='z'||(castr[i]>='A'&&castr[i]<='Z'&&0==find(castr[i])))
//		{
//			int count;
//			for(count=0;count<i;count++)
//				printf("%c",castr[count]);
//			printf("\033[4m\033[1;31m%c\033[0m",castr[count]);
//			count++;
//			for(;count<lenth;count++)
//				printf("%c",castr[count]);
//			printf("\n");
//			printf("\033[1;31m没有该矩阵信息！\033[0m\n");
//			return 0;
//		}
//		printf("now is %dth\n",i);
		if(-1==equal(castr,lenth))
		{
			printf("\033[1;31m是否缺少右括号--')'?\033[0m\n");
//			sleep(2);
			return 0;
		}
		if(1==equal(castr,lenth))
		{
			printf("\033[1;31m是否缺少左括号--'('?\033[0m\n");
//			sleep(2);	
			return 0;
		}

		if(castr[i]>='a'&&castr[i]<='z'||(castr[i]>='A'&&castr[i]<='Z'&&0==find(castr[i])))
		{

			int count;
			for(count=0;count<i;count++)
				printf("%c",castr[count]);
			printf("\033[4m\033[1;31m%c\033[0m",castr[count]);
			count++;
			for(;count<lenth;count++)
				printf("%c",castr[count]);
			printf("\n");
			printf("\033[1;31m没有该矩阵信息！\033[0m\n");
			return 0;
		}

		else if(castr[i]=='!')
		{
			if(i>0||i==lenth-1)
			{
				return 0;
			}
		}

		else if(castr[i]=='+'||castr[i]=='-'||castr[i]=='*'||castr[i]=='/')
		{
			if(!(i-1>=0&&((castr[i-1]>=65&&castr[i-1]<=90)||castr[i-1]==')'||castr[i-1]=='1'||(i>=3&&castr[i-2]=='^')))||!(i+1<lenth&&((castr[i+1]>=65&&castr[i+1]<=90)||castr[i+1]=='('||castr[i+1]=='$')))
			{
				int count;
				for(count=0;count<i;count++)
					printf("%c",castr[count]);
				printf("\033[4m\033[1;31m%c\033[0m",castr[count]);
				count++;
				for(;count<lenth;count++)
					printf("%c",castr[count]);
				printf("\n");
				return 0;
			}
		}

		else if(castr[i]=='|')
		{
			if(!(i+1<lenth&&castr[i+1]=='1')||!(i-1>=0&&(castr[i-1]>=65&&castr[i-1]<=90)||castr[i-1]==')'))
			{
				int count;
				for(count=0;count<i;count++)
					printf("%c",castr[count]);
				printf("\033[4m\033[1;31m%c\033[0m",castr[count]);
				count++;
				for(;count<lenth;count++)
					printf("%c",castr[count]);
				printf("\n");
				return 0;
			}
		}

		else if(castr[i]=='$')
		{
			if(!((i+1<lenth&&(castr[i+1]>='A'&&castr[i+1]<='Z'||castr[i+1]=='(')&&(i==0||castr[i-1]=='+'||castr[i-1]=='-'||castr[i-1]=='*'||castr[i-1]=='/'||castr[i-1]=='!'))))
			{
				int count;
				for(count=0;count<i;count++)
					printf("%c",castr[count]);
				printf("\033[4m\033[1;31m%c\033[0m",castr[count]);
				count++;
				for(;count<lenth;count++)
					printf("%c",castr[count]);
				printf("\n");
				return 0;
			}
		}

		else if(castr[i]=='^')
		{
			if(!(i>0&&i+1<lenth&&(castr[i-1]==')'||castr[i-1]>='A'&&castr[i-1]<='Z')&&castr[i+1]>='1'&&castr[i+1]<='9'))
			{
				int count;
		        for(count=0;count<i;count++)
					printf("%c",castr[count]);
				printf("\033[4m\033[1;31m%c\033[0m",castr[count]);
				count++;
				for(;count<lenth;count++)
					printf("%c",castr[count]);
				printf("\n");
				return 0;
			}
		}
		
		else if(castr[i]>=65&&castr[i]<=90)
		{
			if(i-1>=0&&castr[i-1]>=65&&castr[i-1]<=90||i+1<lenth&&castr[i+1]<=90&&castr[i+1]>=65)
			{
				int count;
				for(count=0;count<i;count++)
					printf("%c",castr[count]);
				printf("\033[4m\033[1;31m%c\033[0m",castr[count]);
				count++;
				for(;count<lenth;count++)
					printf("%c",castr[count]);
				printf("\n");
				return 0;
			}
		}

		else if(castr[i]==')'||castr[i]=='(')
		{
			if(!((i>=1&&castr[i]=='('&&(castr[i-1]=='-'||castr[i-1]=='+'||castr[i-1]=='*'||castr[i-1]=='/'||castr[i-1]=='!'||castr[i-1]=='$'))||i==0||(i>=1&&castr[i]==')'&&(castr[i+1]=='+'||castr[i+1]=='-'||castr[i+1]=='*'||castr[i+1]=='/'||castr[i+1]=='|'||castr[i+1]=='^'))||i==lenth-1))
			{
				int count;
				for(count=0;count<i;count++)
					printf("%c",castr[count]);
				printf("\033[4m\033[1;31m%c\033[0m",castr[count]);
				count++;
				for(;count<lenth;count++)
					printf("%c",castr[count]);
				printf("\n");
				return 0;
			}
		}

		else if(castr[i]!='('&&castr[i]!=')'&&castr[i]!='!'&&!(castr[i]>='1'&&castr[i]<='9'&&castr[i-1]=='^')&&!(castr[i]=='1'&&castr[i-1]=='|'&&castr[i]!='$'))
		{
			int count;
			for(count=0;count<i;count++)
				printf("%c",castr[count]);
			printf("\033[4m\033[1;31m%c\033[0m",castr[count]);
			count++;
			for(;count<lenth;count++)
				printf("%c",castr[count]);
			printf("\n");
			return 0;
		}

	}
	return 1;
}

int find(char ch)
{
	int i=0;
	for(;store[i].row>0;i++)
	{
		if(ch==store[i].name)
			return 1;
	}
	return 0;
}
