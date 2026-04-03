#include "lib/csapp.h"
#include "lib/lib.h"
#include "lib/log.h"

int main() {
  char cmdline[MAXLINE];
  struct JobList **job_list = jobs();

  install_signal_handlers();
  init_log();

  while (1) {
    read_and_evaluate(cmdline, job_list);
  }
}
