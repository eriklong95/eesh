#include "log.h"
#include <stdlib.h>

pid_t fg_pgid;

pid_t get_fg_pgid() {
  eesh_log("Reading %d as foreground job process group ID.\n", fg_pgid);
  return fg_pgid;
}

void set_fg_pgid(pid_t pid) {
  eesh_log("Setting foreground job process group ID to %d.\n", pid);
  fg_pgid = pid;
}