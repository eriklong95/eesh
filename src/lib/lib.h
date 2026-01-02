void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void sigint_handler(int sig);

void setfgpid(pid_t pid);
