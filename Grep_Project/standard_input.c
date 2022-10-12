

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void standard_input(char *b) {
	char c;
	char *a; 
        int i = 0;
        a = (char*)malloc(128*sizeof(char));
        while(scanf("%c", &c) != -1) {
     		if(c == '\n') {
			a[i] = '\0';
	                if(mystrstr(a, b) != NULL)
                        	printf("%s\n", a);
                        free(a);
                        a = (char*)malloc(128*sizeof(char));
                        i = 0;
                }
                else
                        a[i++] = c;
	}
}
