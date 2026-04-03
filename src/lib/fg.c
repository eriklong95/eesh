#include "log.h"
#include <stdlib.h>

pid_t fg_pgid;

pid_t get_fg_pgid() {
  eesh_log("getting fg pgid %d\n", fg_pgid);
  return fg_pgid;
}

void set_fg_pgid(pid_t pid) {
  eesh_log("setting fg pgid %d\n", pid);
  fg_pgid = pid;
}