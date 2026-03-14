#include "job.h"
#include "sig.h"

int parseline(char *, char **);
int builtin_command(char **);
void read_and_evaluate(char *);
