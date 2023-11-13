#ifndef USER_INPUT
#define USER_INPUT

typedef struct cli
{
    char *executable;
} CommandLine;

CommandLine *parse(char *);

#endif
