#include <stdlib.h>

pid_t fg_pgid;

pid_t get_fg_pgid() { return fg_pgid; }

void set_fg_pgid(pid_t pid) { fg_pgid = pid; }