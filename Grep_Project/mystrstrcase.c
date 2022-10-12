


#include "header.h"
#include <stdio.h>
char *mystrstrcase (char *a, char *b) {
	char *p = a, *q = b;
	while(*p != '\0' && *q != '\0') {
		if((*p == *q) || ((*p - 'a' + 'A') == *q) || ((*p + 'a' - 'A') == *q)) {
			p++;
			q++;
		}
		else { 
			if(q == b)
				p++;
			else  {
				p = p - (q - b) + 1;
				q = b;
			}
		}
	}
	if(*q == '\0')
		return a;
	else 
		return NULL;
}
