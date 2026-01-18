#include "job.h"

int parseline(char *, char **);
int builtin_command(char **);
void install_signal_handlers();
void read_and_evaluate(char *, struct JobList **);
