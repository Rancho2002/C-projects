#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
struct customer{
	int acno;
	char name[20];
	char type;
	float bal;
}c1;
void clrscr();
void open_account();
void deposit();
void withdraw();
void show_balance();
void show_all();
void modify_account();
void close_account();

int main(){
	int ch;
	char s1[20],s2[20]="bank";
	int i=0,ans;
	char ch1;
	// Password is "bank"
	printf("Enter your password :");
	while((ch1=getch())!='\r'){
		putch('*');
		s1[i]=ch1;
		i++;
	}
	s1[i]='\0';

	ans=strcmp(s1,s2);
	if(ans==0)
		printf("Welcome to Bank");
	else{
		printf("You are not authorized user");
		getch();exit(0);
	}

	printf("****");
	printf("\n\n\n\n\n\n");
	printf("             ---WELCOME TO THE BANKING MANAGEMENT SYSTEM---      ");
	printf("\t\t\n\n\n\n");
	printf("    *********************************************************************");
	printf("\n\n\n\n\n\n");

	printf("                                PRESS ENTER KEY");
	getch();
	clrscr();

	do{
		clrscr();
		printf("\n Enter");
		printf("\n 1. Open New Account");
		printf("\n 2. Deposit");
		printf("\n 3. Withdraw");
		printf("\n 4. Show Balance");
		printf("\n 5. Show All");
		printf("\n 6. Modify Account");
		printf("\n 7. Close Account.");
		printf("\n 8. Exit\n");
		printf("Enter your choice :");
		scanf("%d",&ch);
		clrscr();
		switch(ch){
			case 1:
				open_account();break;
			case 2:
				deposit();break;
			case 3:
				withdraw();break;
			case 4:
				show_balance();break;
			case 5:
				show_all();break;
			case 6:
				modify_account();break;
			case 7:
				close_account();break;
			case 8:
				break;
			default:
				printf("Incorrect Input");
		}
		printf("Press any key to continue");
		getch();
	}while(ch!=8);
}
void open_account(){
	FILE *fp;
	fp=fopen("bank.bin","rb");
	if(fp==NULL){
		c1.acno=0;
	}
	else{
		while(1){
			fread(&c1,sizeof(c1),1,fp);
			if(feof(fp))
				break;
		}
	}
	c1.acno++;
	fclose(fp);
	printf("\n Enter name:");
	fflush(stdin);
	gets(c1.name);
	while(1){
		printf("Enter S for Saving and C for Current Account:");
		fflush(stdin);
		scanf("%c",&c1.type);
		c1.type=toupper(c1.type);
		if(c1.type=='S' || c1.type=='C')
			break;
		else
			printf("\nInvalid input try again\n");
	}
	printf("\n Enter initial amount to deposit min. 5000 for saving and 10000 for current:");
	scanf("%f",&c1.bal);
	if(c1.type=='S' && c1.bal>=5000 || c1.type=='C' && c1.bal>=10000)
	{
			fp=fopen("bank.bin","ab");
			if(fp==NULL)
			{
				printf("File opening error");
				getch();exit(1);
			}
		fwrite(&c1,sizeof(c1),1,fp);
		printf("\n1 record successfully added\n");
		printf("Your account number is %d\n",c1.acno);
	}
	else
		printf("\nInsufficient fund to open the account\n");
	fclose(fp);
}
void deposit()
{
	FILE *fp;
	int n,found;
	float amount;
	fp=fopen("bank.bin","rb+");
	if(fp==NULL)
	{
		printf("File opening error");
		getch();exit(1);
	}
	printf("\nEnter account number:");
	scanf("%d",&n);
	found=0;
	while(1)
	{
		fread(&c1,sizeof(c1),1,fp);
		if(feof(fp))
			break;
		if(c1.acno==n)
		{
			found=1;
			break;
		}
	}
	if(found==1)
	{
		printf("\nEnter amount to deposit:");
		scanf("%f",&amount);
		c1.bal+=amount;
		printf("\nYour new balance is %.2f",c1.bal);
		fseek(fp,-sizeof(c1),SEEK_CUR);
		fwrite(&c1,sizeof(c1),1,fp);
	}
	else
		printf("\nInvalid account number");
	fclose(fp);
}
void withdraw()
{
	FILE *fp;
	int n,found;
	float amount;
	fp=fopen("bank.bin","rb+");
	if(fp==NULL)
	{
		printf("\nFile opening error");
		getch();exit(1);
	}
	printf("\nEnter account number:");
	scanf("%d",&n);
	found=0;
	while(1)
	{
		fread(&c1,sizeof(c1),1,fp);
		if(feof(fp))
			break;
		if(c1.acno==n)
		{
			found=1;
			break;
		}
	}
	if(found==1)
	{
		printf("\nEnter amount to withdraw:");
		scanf("%f",&amount);
		if(c1.type=='S' && (c1.bal-amount)<5000 || c1.type=='C' && (c1.bal-amount)<10000)
			printf("\nInsufficient funds to withdraw");
		else
		{
			c1.bal-=amount;
			printf("\nYour new balance is %.2f",c1.bal);
			fseek(fp,-sizeof(c1),SEEK_CUR);
			fwrite(&c1,sizeof(c1),1,fp);
		}
	}
	else
		printf("\nInvalid account number");
	fclose(fp);
}
void show_balance()
{
	FILE *fp;
	int n,found;
	float amount;
	fp=fopen("bank.bin","rb");
	if(fp==NULL)
	{
		printf("\nFile opening error");
		getch();exit(1);
	}
	printf("\nEnter account number:");
	scanf("%d",&n);
	found=0;
	while(1)
	{
		fread(&c1,sizeof(c1),1,fp);
		if(feof(fp))
			break;
		if(c1.acno==n)
		{
			found=1;
			break;
		}
	}
	if(found==1)
	{
		printf("\nYour balance is %.2f",c1.bal);
	}
	else
		printf("\nInvalid account number");
	fclose(fp);
}
void show_all()
{
	FILE *fp;
	int n;
	float amount;
	fp=fopen("bank.bin","rb");
	if(fp==NULL)
	{
		printf("\nFile opening error");
		getch();exit(1);
	}
	printf("\nAcno\tName\t\tBalance\n");
	while(1)
	{
		fread(&c1,sizeof(c1),1,fp);
		if(feof(fp))
			break;
		if(strlen(c1.name)>=8)
			printf("%d\t%s\t%.2f\n",c1.acno,c1.name,c1.bal);
		else
			printf("%d\t%s\t\t%.2f\n",c1.acno,c1.name,c1.bal);
	}
	fclose(fp);
}
void modify_account()
{
	FILE *fp;
	int n,found;
	fp=fopen("bank.bin","rb+");
	if(fp==NULL)
	{
		printf("\nFile opening error");
		getch();exit(1);
	}
	printf("\nEnter account number:");
	scanf("%d",&n);
	found=0;
	while(1)
	{
		fread(&c1,sizeof(c1),1,fp);
		if(feof(fp))
			break;
		if(c1.acno==n)
		{
			found=1;
			break;
		}
	}
	if(found==1)
	{
		printf("\n Enter name:");
		fflush(stdin);
		gets(c1.name);
		fseek(fp,-sizeof(c1),SEEK_CUR);
		fwrite(&c1,sizeof(c1),1,fp);
	}
	else
		printf("\nInvalid account number");
	fclose(fp);
}
void close_account()
{
	FILE *fp1,*fp2;
	int n,found;
	fp1=fopen("bank.bin","rb");
	fp2=fopen("temp.bin","wb");
	if(fp1==NULL || fp2==NULL)
	{
		printf("\nFile opening error");
		getch();exit(1);
	}
	printf("\nEnter account number:");
	scanf("%d",&n);
	found=0;
	while(1)
	{
		fread(&c1,sizeof(c1),1,fp1);
		if(feof(fp1))
			break;
		if(c1.acno==n)
		{
			found=1;
		}
		else
			fwrite(&c1,sizeof(c1),1,fp2);
	}
	fclose(fp1);
	fclose(fp2);
	if(found==0)
	{
		printf("\nInvalid account number");
		remove("temp.bin");
	}
	else
	{
		remove("bank.bin");
		rename("temp.bin","bank.bin");
		printf("Record removed successfully");
	}
}
void clrscr()
{
	system("cls");
}





