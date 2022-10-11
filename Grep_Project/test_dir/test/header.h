#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void standard_options(char *, char *);
void standard_input(char *);
void usage();
void recursive(char *, char *, int);
char *mystrstr (char *, char *);
char *mystrstrcase (char *, char *);
char *mystrtok_multi (char *, char *, int);
