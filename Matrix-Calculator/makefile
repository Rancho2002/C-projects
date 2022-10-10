do:main.o frame.o add_matrix.o change.o calculate.o Help.o jisuan.o
	gcc -g -o do main.o frame.o add_matrix.o change.o calculate.o Help.o jisuan.o -lncursesw
main.o:main.c
	gcc -g -c main.c
frame.o:frame.c
	gcc -g -c frame.c
add_matrix.o:add_matrix.c
	gcc -g -c add_matrix.c 
change.o:change.c
	gcc -g -c change.c
calculate.o:calculate.c
	gcc -g -c calculate.c
Help.o:Help.c
	gcc -g -c Help.c -lncursesw
jisuan.o:jisuan.c
	gcc -g -c jisuan.c
clean:
	rm main.o frame.o add_matrix.o change.o calculate.o jisuan.o calc
