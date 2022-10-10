/*************************************************
    > File Name: Hlep.c
    > Author:YOUR_NAME
    > Mail:YOUR_MAIL_ADDRESS
    > Created Time: 2016年05月24日 星期二 16时01分14秒
 ************************************************************************/

#include <stdio.h>
#include <curses.h>
//#include <ncursesw.h>
#include <locale.h>
#include "matrix.h"

void Help()
{
	int x=1;
	int y=1;
	int ch;
	setlocale(LC_ALL,"");
	initscr();
	cbreak();
	keypad(stdscr,true);
	box(stdscr,'|','-');
	noecho();
	start_color();
	refresh();
	
	addstr("\n");
	addstr("**************************************");
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	attron(A_BOLD);
	attron(COLOR_PAIR(1));
	addstr("帮助");
	refresh();
	attroff(COLOR_PAIR(1));
	attroff(A_BOLD);
	addstr("***************************************\n");
	attron(A_BOLD);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	attron(COLOR_PAIR(2));
    addstr("1.该矩阵计算器有哪些具体功能?\n");
	refresh();
	attroff(COLOR_PAIR(2));
	attroff(A_BOLD);
		     //  printw("\033[1;33m%s\033[0m\n","1.该矩阵计算器有哪些具体功能?");
	addstr("    该矩阵计算器的主要功能有：矩阵的录入与矩阵的复合运算。其中，矩阵的录入可分为从键盘输入以及从文件中导入；从文件中导入可以是全部导入也可以是部分导入。矩阵的符合运算是输入矩阵运算表达式，程序会给出计算结果（结果小数部分用分数表示）。\n");
	addstr("\n");
	attron(A_BOLD);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	attron(COLOR_PAIR(2));
	addstr("2.怎样进行矩阵的导入？\n");
	refresh();
	attroff(COLOR_PAIR(2));
	attroff(A_BOLD);
	addstr("    首先在主菜单一栏选择矩阵的导入，然后在导入界面会看到矩阵的导入分为两部分：从文件的导入与从键盘的输入。选择从文件的导入后，会要求输入要导入矩阵的文件名称，如果文件打开成功，系统会给出提示，否则显示文件打开失败！打开成功后有两个选择。一是文件的矩阵全部导入，另一个是从文件中部分导入。选择全部倒入系统会显示导入过程，选择部分显示系统会加载文件中目前有那些矩阵可供导入。\n");
	addstr("\n");
	attron(A_BOLD);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	attron(COLOR_PAIR(2));
	addstr("3.怎样进行矩阵的计算？\n");
	refresh();
	attroff(COLOR_PAIR(2));
	attroff(A_BOLD);
	addstr("    矩阵的计算很容易。首先在主菜单一栏选择矩阵计算，然后按照相关提示输入您想要计算的表达式。如果输入错误会给出相应提示。\n");
	addstr(" 比如输入：(A+B)-C*D-B|1\n");
	addstr("\n");
	attron(A_BOLD);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	attron(COLOR_PAIR(2));
	addstr("4.我能够使用什么操作符？\n");
	refresh();
	attroff(COLOR_PAIR(2));
	attroff(A_BOLD);
	addstr("    目前该系统支持的操作符有：'+',   '-',   '*',   '/',   '|1',   '!',   '()',   '$',   '^'\n");
	addstr("    '+' 表示相加:  A+B\n");
	addstr("    '-' 表示相减: A-B\n");
	addstr("    '*' 表示相乘: A*B\n");
	addstr("    '/' 表示相除: A/B\n");
	addstr("    '|1' 表示求逆: A|1\n");
	addstr("    '()' 表示先计算括号里的内容: (A-B)\n");
	addstr("    '!' 表示对后面的矩阵求行列式: !(A-B)*C\n");
	addstr("    '$' 表示求矩阵的转置: $A\n");
	addstr("    '^' 表示求矩阵的次方: A^2\n");
	addstr("\n");
	attron(A_BOLD);
	init_pair(3,COLOR_BLUE,COLOR_BLACK);
	attron(COLOR_PAIR(3));
	addstr("按Esc键退出帮助！\n");
	refresh();
	attroff(COLOR_PAIR(3));
	attroff(A_BOLD);
							   
	move(x,y);
	do
	{
	     ch = getch();
		 switch(ch)
		 {
			case KEY_UP:
				{
					--x;
					break;
				}
		    case KEY_DOWN: 
				{
					++x;
					break;
				}
			case KEY_RIGHT:
				{
					++y;
					break;
				}
			case KEY_LEFT:
				{
					--y;
					break;
				}
			case ' ':
				{
					++y;
					int ch1=' ';
					addch(ch1);
					break;
				}
			case '/t':
				{
					x+=7;
					break;
				}
			case KEY_BACKSPACE:
				{
					mvaddch(x,--y,' ');					
					break;
				}
			case 27:
				{
					endwin();
					return;
				}
			default:
				{
					insch(ch);
					y++;
					break;
				}
		 }
		 move(x,y);
		 refresh();
	}while(1);

/*	addstr("\n");
	addstr("**************************************");
	attron(A_BOLD);
	addstr("帮助");
	attroff(A_BOLD);
	addstr("***************************************\n");
	attron(A_BOLD);
	addstr("1.该矩阵计算器有哪些具体功能?\n");
	attroff(A_BOLD);
//	printw("\033[1;33m%s\033[0m\n","1.该矩阵计算器有哪些具体功能?");
	addstr("	该矩阵计算器的主要功能有：矩阵的录入与矩阵的复合运算。其中，矩阵的录入可分为从键盘输入以及从文件中导入；从文件中导入可以是全部导入也可以是部分导入。矩阵的符合运算是输入矩阵运算表达式，程序会给出计算结果（结果小数部分用分数表示）。\n");
	addstr("\n");
	attron(A_BOLD);
	addstr("2.怎样进行矩阵的导入？\n");
	attroff(A_BOLD);
	addstr("	首先在主菜单一栏选择矩阵的导入，然后在导入界面会看到矩阵的导入分为两部分：从文件的导入与从键盘的输入。选择从文件的导入后，会要求输入要导入矩阵的文件名称，如果文件打开成功，系统会给出提示，否则显示文件打开失败！打开成功后有两个选择。一是文件的矩阵全部导入，另一个是从文件中部分导入。选择全部倒入系统会显示导入过程，选择部分显示系统会加载文件中目前有那些矩阵可供导入。\n");
	addstr("\n");
	attron(A_BOLD);
	addstr("3.怎样进行矩阵的计算？\n");
	attroff(A_BOLD);
	addstr("	矩阵的计算很容易。首先在主菜单一栏选择矩阵计算，然后按照相关提示输入您想要计算的表达式。如果输入错误会给出相应提示。\n");
	addstr(" 比如输入：(A+B)-C*D-B|1\n");
	addstr("\n");
	attron(A_BOLD);
	addstr("4.我能够使用什么操作符？\n");
	attroff(A_BOLD);
	addstr("	目前该系统支持的操作符有：'+',   '-',   '*',   '/',   '|1',   '!',   '()',   '$',   '^'\n");
	addstr("	'+' 表示相加:  A+B\n");
	addstr("	'-' 表示相减: A-B\n");
	addstr("	'*' 表示相乘: A*B\n");
	addstr("	'/' 表示想除: A/B\n");
	addstr("	'|1' 表示求逆: A|1\n");
	addstr("	'()' 表示先计算括号里的内容: (A-B)\n");
	addstr("	'!' 表示对后面的矩阵求行列式: !(A-B)*C\n");
	addstr("	'$' 表示求矩阵的转置: $A\n");
	addstr("	'^' 表示求矩阵的次方: A^2\n");
	refresh();
//	printf("\n");
//	addstr("\033[0;44m                                                                                 \033[0m\n");
//	addstr("Exit can input 'Enter' ");
//	if(choice=='\n')
//		return;
//	addstr("*********************************************************************************\n");
	int ch;
	ch=getch();
	endwin();
*/
}
