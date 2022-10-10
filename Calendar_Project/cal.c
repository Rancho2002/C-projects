#include<stdio.h>
int daysIN_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
char *months[]=
{
	" ",
	"\n\n\nJanuary",
	"\n\n\nFebruary",
	"\n\n\nMarch",
	"\n\n\nApril",
	"\n\n\nMay",
	"\n\n\nJune",
	"\n\n\nJuly",
	"\n\n\nAugust",
	"\n\n\nSeptember",
	"\n\n\nOctober",
	"\n\n\nNovember",
	"\n\n\nDecember"
};


int determinedaycode(int year)
{
	int daycode;
	int d1, d2, d3;
	
	d1 = (year - 1.)/ 4.0;
	d2 = (year - 1.)/ 100.;
	d3 = (year - 1.)/ 400.;
	daycode = (year + d1 - d2 + d3) %7;
	return daycode;
}


int getleapyear(int year)
{
	if(year%4==0&&year%100!=0||year%400==0)
	{
		daysIN_month[2]=29;
		return 1;                       //obviously
	}
	else
	{
		daysIN_month[2] = 28;
		return 0;
	}
}

void calendar(int year, int daycode)
{
	int month, day;
	for ( month = 1; month <= 12; month++ )
	{
		printf("%s", months[month]);
		printf("\n\nSun  Mon  Tue  Wed Thu  Fri  Sat\n" );
		
		for (day=1;day<=1+daycode*5;day++)
		{
			printf(" ");
		}
		for(day=1;day<=daysIN_month[month];day++ )
		{
			printf("%2d", day );
			
			if((day+daycode)%7>0)
				printf("   " );
			else
				printf("\n " );
		}
			daycode = ( daycode + daysIN_month[month] ) % 7;
	}
}

int main()
{
	int year, daycode, leapyear;
	printf("Please enter a year to get the calendar");
	scanf("%d", &year);
	
	daycode = determinedaycode(year);
	getleapyear(year);
	printf("\nCalendar %d",year);
	calendar(year, daycode);
	printf("\n");
}
