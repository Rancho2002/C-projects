/*************************************************************************
    > File Name: jisuan.c
    > Author:YOUR_NAME
    > Mail:YOUR_MAIL_ADDRESS
    > Created Time: 2016年05月27日 星期五 21时00分29秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "math.h"
#include "matrix.h"
#include "string.h"

int num=0;

char Inver(char ch)
{
	int f,s;
	for(f=0;count[f].row>0;f++);
	count[f].name='a'+num;
	num++;
	for(s=0;count[s].name!=ch;s++);
	if(count[s].row!=count[s].col)
	{
		printf("\033[1;33m存在矩阵不能求逆，无法计算！请检查能否相除或求逆\033[0m\n");
		printf("\n");
		sleep(2);
		return '?';
	}
	int line=count[s].row;
	count[f].row=line;
	count[f].col=line;
	float t[10][10];
	int i,j,k;
	float max,temp;
	for(i=0;i<line;i++)
	{
		for(j=0;j<line;j++)
		{
			t[i][j]=count[s].value[i][j];
		}
	}
	
	for(i=0;i<line;i++)
	{
		for(j=0;j<line;j++)
		{
			count[f].value[i][j]=(i==j)?(float)1:0;
		}
	}

	for(i=0;i<line;i++)
	{
		max=t[i][i];
		k=i;
		for(j=i+1;j<line;j++)
		{
			if(fabs(t[j][i])>fabs(max))
			{
				max=t[j][i];
				k=j;
			}
		}

		if(k!=i)
		{
			for(j=0;j<line;j++)
			{
				temp=t[i][j];
				t[i][j]=t[k][j];
				t[k][j]=temp;

				temp=count[f].value[i][j];
				count[f].value[i][j]=count[f].value[k][j];
				count[f].value[k][j]=temp;
			}
		}

		if(t[i][i]==0)
		{
			printf("\033[1;33m存在矩阵不能求逆，无法计算！请检查能否相除或求逆\033[0m\n");
			sleep(2);
			return '?';
		}

		temp=t[i][i];
		for(j=0;j<line;j++)
		{
			t[i][j]=t[i][j]/temp;
			count[f].value[i][j]=count[f].value[i][j]/temp;
		}

		for(j=0;j<line;j++)
		{
			if(j!=i)
			{
				temp=t[j][i];
				for(k=0;k<line;k++)
				{
					t[j][k]=t[j][k]-t[i][k]*temp;
					count[f].value[j][k]=count[f].value[j][k]-count[f].value[i][k]*temp;
				}
			}
		}
		
	}
//	int r,c;
//	for(r=0;r<line;r++)
//	{
//		for(c=0;c<line;c++)
//		{
//			printf("%f ",count[f].value[r][c]);
//		}
//		printf("\n");
//	}
	return count[f].name; 
}

/*int over(char *castr)
{
	int i;
	int lenth;
	lenth=strlen(castr);
	for(i=0;i<lenth;i++)
	{
		if(castr[i]=='-'||castr[i]=='+'||castr[i]=='*'||castr[i]=='/'||castr[i]=='|'||castr[i]=='('||castr[i]==')')
			return 0;
	}	
	return 1;
}*/

char multiply(char ch1,char ch2)
{
	int i;
	for(i=0;count[i].row>0;i++);
	int s1,s2;
	for(s1=0;count[s1].name!=ch1;s1++);
	for(s2=0;count[s2].name!=ch2;s2++);
	if(count[s1].col!=count[s2].row)
	{
		printf("\033[1;33m存在矩阵不能求逆，无法计算！请检查能否相除或求逆\033[0m\n");
		sleep(2);
		return '?';
	}
	count[i].name='a'+num;
	num++;
	count[i].row=count[s1].row;
	count[i].col=count[s2].col;
	int r1,cr,c2;
	for(r1=0;r1<count[i].row;r1++)
	{
		for(c2=0;c2<count[i].col;c2++)
		{
			for(cr=0;cr<count[s1].col;cr++)
			{
				count[i].value[r1][c2]+=count[s1].value[r1][cr]*count[s2].value[cr][c2];
			}
		}
	}

	return count[i].name;
}

char divide(char ch1,char ch2)
{
	char rev=Inver(ch1);
	if(rev=='?')
		return '?';
/*	int index;
	for(index=0;count[index].name!=rev;index++);
	int row=count[index].row;
	int col=count[index].col;
	int i,j;
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			printf("%f ",count[index].value[i][j]);
		}
		printf("\n");
	}
*/
	char res=multiply(ch2,rev);
	return res;
}

char plus(char ch1,char ch2)
{
	int i;
	for(i=0;count[i].row>0;i++);
	int s1,s2;
	for(s1=0;count[s1].name!=ch1;s1++);
	for(s2=0;count[s2].name!=ch2;s2++);
	if(!(count[s1].row==count[s2].row&&count[s1].col==count[s2].col))
	{
		printf("\033[1;33m存在矩阵不能相加，请检查矩阵行数列数是否一致\033[0m\n");
		sleep(2);
		return '?';
	}
	count[i].name='a'+num;
	count[i].row=count[s1].row;
	count[i].col=count[s2].col;

	int r,c;
	for(r=0;r<count[i].row;r++)
	{
		for(c=0;c<count[i].col;c++)
		{
			count[i].value[r][c]=count[s1].value[r][c]+count[s2].value[r][c];
		}
	}
	num++;
	return count[i].name;
}

char minus(char ch1,char ch2)
{
	int i;
	for(i=0;count[i].row>0;i++);
	int s1,s2;
	for(s1=0;count[s1].name!=ch1;s1++);
	for(s2=0;count[s2].name!=ch2;s2++);
	if(!(count[s1].row==count[s2].row&&count[s1].col==count[s2].col))
	{
		printf("\033[1;33m存在矩阵不能相减，请检查矩阵行数列数是否一致\033[0m\n");
		sleep(2);
		return '?';
	}
	count[i].name='a'+num;
	num++;
	count[i].row=count[s1].row;
	count[i].col=count[s1].col;

	int r,c;
	for(r=0;r<count[i].row;r++)
	{
		for(c=0;c<count[i].col;c++)
		{
			count[i].value[r][c]=count[s1].value[r][c]-count[s2].value[r][c];
		}
	}
	return count[i].name;
}

char Top(char ch,int n)
{
	int count=1;
	for(;count<n;count++)
	{
		ch=multiply(ch,ch);
	}
	return ch;
}

char zhuanzhi(char ch)
{
	int i;
	for(i=0;count[i].row>0;i++);
	int s;
	for(s=0;count[s].name!=ch;s++);
	int row=count[s].row;
	int col=count[s].col;
	count[i].name='a'+num;
	num++;
	count[i].row=col;
	count[i].col=row;

	int c,r;
	for(r=0;r<row;r++)
	{
		for(c=0;c<col;c++)
		{
			count[i].value[c][r]=count[s].value[r][c];
		}
	}
	return count[i].name;
}

int exit0(char *castr)
{
	int lenth=strlen(castr);
	int i;
	for(i=0;i<lenth;i++)
	{
		if(castr[i]=='*'||castr[i]=='/')
			return 1;
	}
	return 0;
}

int exit1(char *castr)
{
	int lenth=strlen(castr);
	int i;
	for(i=0;i<lenth;i++)
	{
		if(castr[i]=='('||castr[i]==')')
			return 1;
	}
	return 0;
}

int exit2(char *castr)
{
	int lenth=strlen(castr);
	int i;
	for(i=0;i<lenth;i++)
	{
		if(castr[i]=='|')
			return 1;
	}
	return 0;
}

int exit3(char *castr)
{
	int lenth=strlen(castr);
	int i;
	for(i=0;i<lenth;i++)
	{
		if(castr[i]=='^')
			return 1;
	}

	return 0;
}

int exit4(char *castr)
{
	int lenth=strlen(castr);
	int i;
	for(i=0;i<lenth;i++)
	{
		if(castr[i]=='$')
			return 1;
	}
	return 0;
}




char jisuan(char *castr)
{
	int lenth;
	lenth=strlen(castr);
//	if(1==over(castr))
//	{
//		return castr;
//	}
	
	int index2;	
	do
	{
		for(index2=0;index2<lenth;index2++)
                {
                        if(castr[index2]==')')
                        {
                                int index3=1;
                                for(;castr[index2-index3]!='(';index3++);
                                char minstr[10]="\0";
                                int j;
                                int w=0;
                                for(j=index2-index3+1;j<index2;j++)
                                {
                                        minstr[w]=castr[j];
                                        w++;
                                }
                                char ch;
                                ch=jisuan(minstr);
                                castr[index2-index3]=ch;
                                for(j=index2-index3+1;j<lenth-index3;j++)
                                {
                                        castr[j]=castr[j+index3];
                                }
                                for(j=lenth-index3;j<lenth;j++)
                                {
                                        castr[j]='\0';
                                }
                                lenth-=index3;
                                break;
                        }
                }
        }while(1==exit1(castr));
//	printf("%s\n",castr);
	
	int index1;
	do
	{
		for(index1=0;index1<lenth;index1++)
		{
			if(castr[index1]=='|')
			{
				castr[index1-1]=Inver(castr[index1-1]);
				if('?'==castr[index1-1])
				{
					return '?';
				}

				int i;
				for(i=index1;i<lenth-2;i++)
				{	
					castr[i]=castr[i+2];
				}
				castr[lenth-1]='\0';
				castr[lenth-2]='\0';
				lenth-=2;
				break;
			}
		}
		
	}while(1==exit2(castr));

	int index7;
	do
	{
		for(index7=0;index7<lenth;index7++)
		{
			if(castr[index7]=='$')
			{
				castr[index7]=zhuanzhi(castr[index7+1]);
				if('?'==castr[index7])
				{
					return '?';
				}

				int i;
				for(i=index7+1;i<lenth-1;i++)
				{
					castr[i]=castr[i+1];
				}
				castr[lenth-1]='\0';
				lenth-=1;
				break;
			}
		}
	}while(1==exit4(castr));


	int index6;
	do
	{
		for(index6=0;index6<lenth;index6++)
		{
			if(castr[index6]=='^')
			{
				int n;
				n=castr[index6+1]-'0';
				castr[index6-1]=Top(castr[index6-1],n);
				if('?'==castr[index6-1])
				{
					return '?';
				}
		
				int i;
				for(i=index6;i<lenth-2;i++)
				{
					castr[i]=castr[i+2];
				}
				castr[lenth-1]='\0';
				castr[lenth-2]='\0';
				lenth-=2;
				break;
			}
		}
	}while(1==exit3(castr));
	
	int index4;
	do
	{
		for(index4=0;index4<lenth;index4++)
		{
			if(castr[index4]=='*')
			{
				char mul;
				mul=multiply(castr[index4-1],castr[index4+1]);
				if(mul=='?')
					return '?';
				castr[index4-1]=mul;
				int j;
				for(j=index4;j<lenth-2;j++)
				{
					castr[j]=castr[j+2];
				}
				castr[lenth-1]='\0';
				castr[lenth-2]='\0';
				lenth-=2;
				break;
			}
		
			else if(castr[index4]=='/')
			{
				char div;
				div=divide(castr[index4-1],castr[index4+1]);
				if('?'==div)
				{
					return '?';
				}
				castr[index4-1]=div;
				int j;
				for(j=index4;j<lenth-2;j++)
				{
					castr[j]=castr[j+2];
				}
				castr[lenth-1]='\0';
				castr[lenth-2]='\0';
				lenth-=2;
				break;
			}
		}
	}while(1==exit0(castr));

//	printf("%s\n",castr);

	int index5;
	do
	{
		for(index5=0;index5<lenth;index5++)
		{
			if(castr[index5]=='+')
			{
				char plu;
				plu=plus(castr[index5-1],castr[index5+1]);
				if(plu=='?')
					return '?';
				castr[index5-1]=plu;
				int j;
				for(j=index5;j<lenth-2;j++)
				{
					castr[j]=castr[j+2];
				}
				castr[lenth-1]='\0';
				castr[lenth-2]='\0';
				lenth-=2;				
				break;
			}

			else if(castr[index5]=='-')
			{
				char min;
				min=minus(castr[index5-1],castr[index5+1]);
				if(min=='?')
					return '?';
				castr[index5-1]=min;
				int j;
				for(j=index5;j<lenth-2;j++)
				{
					castr[j]=castr[j+2];
				}
				castr[lenth-1]='\0';
				castr[lenth-2]='\0';
				lenth-=2;
				break;
			}
		}
	}while(lenth>1);
//	printf("%s\n",castr);
	
	char result;
	result=castr[0];
	
	return result;
}
