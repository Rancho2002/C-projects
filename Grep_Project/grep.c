

#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>     
#include "header.h"
int main(int argc, char *argv[]) {
	int f[10], size[10], i = 0;
	char *a;	
	char s[2] = "\n";
   	char *token;
	if(argc == 1) {
		printf("Use ./project -h command for usage\n");
		exit(1);
	}
	else if(strcmp(argv[1],"-h") == 0 && argv[2] == NULL) {
		usage();
		exit(1);
	}
	if(argc < 3 && strcmp(argv[0], "./project") != 0) {
		errno = EINVAL;
		perror("Bad arguments");
		return errno; 
	}
	else if(argc < 3 || (argc < 4 && argv[1][0] == '-')) {
		if(argc < 3)
			standard_input(argv[1]);
		if(argc < 4)
			standard_options(argv[1], argv[2]);
		exit(1);
	}	
	if(strcmp(argv[1],"-r") == 0 || strcmp(argv[1], "-ri") == 0 || strcmp(argv[1], "-rv") == 0) {
		DIR *dir;
		char dname[32];
   		dir = opendir(argv[3]);
  		struct dirent *dent;
  		if(dir!=NULL) {
       			while((dent = readdir(dir))) {
				if(dent->d_type == DT_DIR) {
					if(strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0);
					else  {
						strcpy(dname, argv[3]);
						strcat(dname, "/");
						strcat(dname, dent->d_name);
						if(strcmp(argv[1], "-r") == 0)
							recursive(dname, argv[2], 0);
						if(strcmp(argv[1], "-ri") == 0)
							recursive(dname, argv[2], 1);
						if(strcmp(argv[1], "-rv") == 0)
							recursive(dname, argv[2], 2);
					}
				}
				else if(f[i] = open(dent->d_name, O_RDONLY)) { 
					size[i] = lseek(f[i], 0, SEEK_END);
					a = (char*)malloc(size[i]*sizeof(char));
					lseek(f[i], 0, 0);	
					read(f[i], a, size[i]*sizeof(char));
   					token = mystrtok_multi(a, s, i);
 					while( token != NULL ) { 
						if((mystrstr(token, argv[2]) != NULL && strcmp(argv[1], "-r") == 0) || (mystrstrcase(token, argv[2]) != NULL && strcmp(argv[1], "-ri") == 0) || (mystrstr(token, argv[2]) == NULL && strcmp(argv[1], "-rv") == 0) ) {
							printf("%s%s/%s%s:%s%s\n", KMAG, argv[3], dent->d_name, KBLU, KNRM, token);
						}
						token = mystrtok_multi(NULL, s, i);
  	 				}
				close(f[i]);
				free (a);
				}
				i++;
			}
           		closedir(dir);
			return 0;
		}
	}
	else if(strncmp(argv[1], "-m", 2) == 0) {
		int count[10];
		int num = atoi(&argv[1][2]);
                for(i = 0; i < 10; i++)
                        count[i] = 0;
                for(i = 1; i <= 10; i++) {
                        f[i] = open(argv[i+2], O_RDONLY);
                        size[i] = lseek(f[i], 0, SEEK_END);
                }
                for(i = 1; i <= 10; i++) {
                        a = (char*)malloc(size[i]*sizeof(char));
                        lseek(f[i], 0, 0);
                        read(f[i], a, size[i]*sizeof(char));
                        token = mystrtok_multi(a, s, i);
                        while( token != NULL ) {
                                if(mystrstr( token, argv[2]) != NULL) {
					if(argc < 5)
                                                printf("%s\n", token);
                                        else
                                                printf("%s%s : %s%s\n", KMAG, argv[i+2], KNRM, token);

                                        count[i-1]++;
					if(count[i-1] == num)
						break;
                                }
                                token = mystrtok_multi(NULL, s, i);
                        }
                        close(f[i]);
                        free (a);
                }
                return 0;

	}
	else if(strncmp(argv[1], "-A", 2) == 0) {
                int num = atoi(&argv[1][2]);
		int j = 0;
                for(i = 1; i <= 10; i++) {
                        f[i] = open(argv[i+2], O_RDONLY);
                        size[i] = lseek(f[i], 0, SEEK_END);
                }
                for(i = 1; i <= 10; i++) {
                        a = (char*)malloc(size[i]*sizeof(char));
                        lseek(f[i], 0, 0);
                        read(f[i], a, size[i]*sizeof(char));
                        token = mystrtok_multi(a, s, i);
                        while( token != NULL ) {
                                if(mystrstr( token, argv[2]) != NULL) {
                                        if(argc < 5)
                                                printf("%s\n", token);
                                        else
                                                printf("%s%s : %s%s\n", KMAG, argv[i+2], KNRM, token);
					for(j = 0; j <= num; j++) {
						token = mystrtok_multi(NULL, s, i);
						if(token == NULL)
							break;
                                		if(mystrstr( token, argv[2]) != NULL)
							j = 0;
						if(argc < 5)
                                                	printf("%s\n", token);
                                        	else
                                                	printf("%s%s : %s%s\n", KMAG, argv[i+2], KNRM, token);
					}

                                }
                                token = mystrtok_multi(NULL, s, i);
                        }
                        close(f[i]);
                        free (a);
                }
                return 0;

        }

	else if(strcmp(argv[1], "-w") == 0) {
                char *p;
                for(i = 1; i <= 10; i++) {
                        f[i] = open(argv[i+2], O_RDONLY);
                        size[i] = lseek(f[i], 0, SEEK_END);
                }
                for(i = 1; i <= 10; i++) {
                        a = (char*)malloc(size[i]*sizeof(char));
                        lseek(f[i], 0, 0);
                        read(f[i], a, size[i]*sizeof(char));
                        token = mystrtok_multi(a, s, i);
                        while( token != NULL ) {
                                if(p = mystrstr(token, argv[2])) {
                                        if(isalpha(*(p - 1)) == 0 && isalpha(*(p + strlen(argv[2]))) == 0) {
                                                if(argc < 5)
                                                        printf("%s\n", token);
                                                else
                                                        printf("%s%s : %s%s\n", KMAG, argv[i+2], KNRM, token);
                                        }
                                }
                                token = mystrtok_multi(NULL, s, i);
                        }
                        close(f[i]);
                        free (a);
                }
                return 0;

        }
	else if(strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "-L") == 0 || strcmp(argv[1], "-il") == 0 || strcmp(argv[1], "-li") == 0 || strcmp(argv[1], "-iL") == 0 || strcmp(argv[1], "-Li") == 0) {
		for(i = 1; i <= 10; i++) {
        	        f[i] = open(argv[i+2], O_RDONLY);
                        size[i] = lseek(f[i], 0, SEEK_END);
                }
                for(i = 1; i <= 10; i++) {
			int FLAG = 0;
                        a = (char*)malloc(size[i]*sizeof(char));
                        lseek(f[i], 0, 0);
                        read(f[i], a, size[i]*sizeof(char));
                        token = mystrtok_multi(a, s, i);
			if(strcmp(argv[1], "-Li") == 0 || strcmp(argv[1], "-iL") == 0 || strcmp(argv[1], "-li") == 0 || strcmp(argv[1], "-il") == 0) {
                        	while( token != NULL ) {
                                	if(mystrstrcase( token, argv[2]) != NULL) {
						FLAG = 1;
						break;
                                	}
                                	token = mystrtok_multi(NULL, s, i);
				}
				if(FLAG == 1 && (strcmp(argv[1], "-li") == 0 || strcmp(argv[1], "-il") == 0)) { 
                                	printf("%s%s\n", KMAG, argv[i+2]);
				}
                                if(FLAG == 0 && (strcmp(argv[1], "-Li") == 0 || strcmp(argv[1], "-iL") == 0)) {
					if(argv[i+2] == NULL)
						break;
                                        printf("%s%s\n", KMAG, argv[i+2]);
				}
			}
			else {
				while( token != NULL ) {
                                        if(mystrstr( token, argv[2]) != NULL) {
						FLAG = 1;
                                                break;
                                        }
                                        token = mystrtok_multi(NULL, s, i);
				}
                                if(strcmp(argv[1], "-l") == 0 && FLAG == 1) {
                                        printf("%s%s\n", KMAG, argv[i+2]);
				}
                                if(strcmp(argv[1], "-L") == 0 && FLAG == 0) {
					if(argv[i+2] == NULL)
						break;
                                        printf("%s%s\n", KMAG, argv[i+2]);
				}
			}
                        close(f[i]);
                        free (a);
                }
                return 0;

	}
	else if(strcmp(argv[1],"-v") == 0 || strcmp(argv[1],"-vn") == 0 || strcmp(argv[1],"-nv") == 0) {
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++) {
			int line_num = 0;
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = mystrtok_multi(a, s, i);
 			while( token != NULL ) { 
				line_num++;
				if(mystrstr( token, argv[2]) == NULL) {
					if(strcmp(argv[1],"-vn") == 0 || strcmp(argv[1],"-nv") == 0) {
						if(argc < 5)
							printf("%s%d%s:%s%s\n", KGRN, line_num, KBLU, KNRM, token);
						else
							printf("%s%s %s: %s%d %s: %s%s\n", KMAG, argv[i+2], KBLU, KGRN, line_num, KBLU, KNRM, token);
					}
					else {
						if(argc < 5)
							printf("%s\n", token);
						else
							printf("%s%s %s: %s%s\n", KMAG, argv[i+2], KBLU, KNRM, token);
					}
				}
				token = mystrtok_multi(NULL, s, i);
  	 		}
			close(f[i]);
			free (a);
		}
		return 0;
	}
	else if(strcmp(argv[1],"-i") == 0 || strcmp(argv[1],"-in") == 0 || strcmp(argv[1],"-in") == 0) {
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++) {
			int line_num = 0;
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = mystrtok_multi(a, s, i);
 			while( token != NULL ) { 
				line_num++;
				if(mystrstrcase( token, argv[2]) != NULL) {
					if(strcmp(argv[1],"-in") == 0 || strcmp(argv[1],"-ni") == 0) {
						if(argc < 5)
							printf("%s%d%s:%s%s\n", KGRN, line_num, KBLU, KNRM, token);
						else
							printf("%s%s %s: %s%d %s: %s%s\n", KMAG, argv[i+2], KBLU, KGRN, line_num, KBLU, KNRM, token);
					}
					else {
						if(argc < 5)
							printf("%s\n", token);
						else
							printf("%s%s %s: %s%s\n", KMAG, argv[i+2], KBLU, KNRM, token);
					}
				}
				token = mystrtok_multi(NULL, s, i);
  	 		}
			close(f[i]);
			free (a);
		}
		return 0;
	}
	else if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-cv") == 0 || strcmp(argv[1], "-vc") == 0) {
		int count[10];
		for(i = 0; i < 10; i++)
			count[i] = 0;
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++) {
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = mystrtok_multi(a, s, i);
 			while( token != NULL ) { 
				if(strcmp(argv[1], "-c") == 0) {
					if(mystrstr( token, argv[2]) != NULL) {
						count[i-1]++;
					}
				}
				else {
					if(mystrstr( token, argv[2]) == NULL) {
						count[i-1]++;
					}
				}
				token = mystrtok_multi(NULL, s, i);
  	 		}
			if(f[i] != -1) {
				if(argc < 5)
					printf("%d\n", count[i-1]);
				else
					printf("%s%s %s: %s%d\n", KMAG, argv[i+2], KBLU, KNRM, count[i-1]);
			}
			close(f[i]);
			free (a);
		}
		return 0;
	}
	else if(strcmp(argv[1], "-n") == 0) {
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++) {
			int line_num = 0;
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = mystrtok_multi(a, s, i);
 			while( token != NULL ) { 
				line_num++;
				if(mystrstr( token, argv[2]) != NULL) {
					if(argc < 5)
						printf("%s%d%s:%s%s\n", KGRN, line_num, KBLU, KNRM, token);
					else
						printf("%s%s %s: %s%d %s: %s%s\n", KMAG, argv[i+2], KBLU, KGRN, line_num, KBLU, KNRM, token);
				}
				token = mystrtok_multi(NULL, s, i);
  	 		}
			close(f[i]);
			free (a);
		}
		return 0;
	}
	else if(strcmp(argv[1], "-b") == 0) {
                for(i = 1; i <= 10; i++) {
                        f[i] = open(argv[i+2], O_RDONLY);
                        size[i] = lseek(f[i], 0, SEEK_END);
                }
                for(i = 1; i <= 10; i++) {
                        int bytes = 0;
                        a = (char*)malloc(size[i]*sizeof(char));
                        lseek(f[i], 0, 0);
                        read(f[i], a, size[i]*sizeof(char));
                        token = mystrtok_multi(a, s, i);
                        while( token != NULL ) {
                                if(mystrstr( token, argv[2]) != NULL) {
                                        if(argc < 5)
                                                printf("%s%d%s:%s%s\n", KGRN, bytes, KBLU, KNRM, token);
                                        else
                                                printf("%s%s %s: %s%d %s: %s%s\n", KMAG, argv[i+2], KBLU, KGRN, bytes, KBLU, KNRM, token);
                                }
				bytes = bytes + strlen(token) + 1;
                                token = mystrtok_multi(NULL, s, i);
                        }
                        close(f[i]);
                        free (a);
                }
                return 0;
        }
	else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-H") == 0 ) {
		for(i = 1; i <= 10; i++) {
                        f[i] = open(argv[i+2], O_RDONLY);
                        size[i] = lseek(f[i], 0, SEEK_END);
                }
                for(i = 1; i <= 10; i++) {
                        a = (char*)malloc(size[i]*sizeof(char));
                        lseek(f[i], 0, 0);      
                        read(f[i], a, size[i]*sizeof(char));
                        token = mystrtok_multi(a, s, i);
                        while( token != NULL ) { 
                                if(mystrstr(token, argv[2]) != NULL) {
                                        if(strcmp(argv[1], "-h") == 0)
                                                printf("%s\n", token);
                                        else
                                                printf("%s%s : %s%s\n", KMAG, argv[i+2], KNRM, token);
                                }
                                token = mystrtok_multi(NULL, s, i);
                        }
                        close(f[i]);
                        free (a);
                }
                return 0;

	}
	else {
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+1], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++) {
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = mystrtok_multi(a, s, i);
 			while( token != NULL ) { 
				if(mystrstr( token, argv[1]) != NULL) {
					if(argc < 4)
						printf("%s\n", token);
					else
						printf("%s%s : %s%s\n", KMAG, argv[i+1], KNRM, token);
				}
				token = mystrtok_multi(NULL, s, i);
  	 		}
			close(f[i]);
			free (a);
		}
		return 0;
	}
}
