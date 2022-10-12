


#include <string.h>
#include "header.h"
#include <stdio.h>
char *mystrstr (char *a, char *b) {
	char *p = a, *q = b;
	while(*p != '\0' && *q != '\0') {
		if(*p == *q)  {
			p++;
			q++;
		}
		else { 
			if(q == b)
				p++;
			else  {
				p = p - (q- b) + 1;
				q = b;
			}
		}
	}
	if(*q == '\0')
		return p - strlen(b);
	else 
		return NULL;
}
