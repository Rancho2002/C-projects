run : grep.o mystrtok_multi.o mystrstr.o mystrstrcase.o dir.o usage.o standard_input.o standard_options.o
	gcc -Wall -o project *.o
grep : grep.c header.h
	gcc -c grep.c
tok : mystrtok_multi.c header.h
	gcc -c mystrtok_multi.c 
str : mystrstr.c mystrstrcase.c header.h
	gcc -c mystrstr.c mystrstrcase.c
dir : dir.c header.h
	gcc -c dir.c
usage : usage.c header.h
	gcc -c usage.c
stdi : standard_input.c header.h
	gcc -c standard_input.c
stdo : standard_options.c header.h
	gcc -c standard_options.c
clean :
	rm *.o
