#include "csapp.h"
#include "fg.h"
#include "job.h"
#include <signal.h>

void sigchld_handler(int sig) {
  int olderrno = errno;
  pid_t pid;
  struct JobList **job_list = jobs();

  while ((pid = waitpid(-1, NULL, 0)) > 0) {
    remove_job(job_list, pid);
  }

  if (errno != ECHILD) {
    sio_error("waitpid error");
  }

  errno = olderrno;
}

void sigint_handler(int sig) {
  pid_t fg = get_fg_pgid();
  if (fg != 0) {
    Kill(-fg, SIGINT);
  }
  Sio_puts("\n");
}

void sigtstp_handler(int sig) {
  pid_t fg = get_fg_pgid();
  if (fg != 0) {
    Kill(-fg, SIGTSTP);
    Sio_puts("Stopped ");
    Sio_putl(fg);
    Sio_puts("\n");
    set_fg_pgid(0);
  }
  Sio_puts("\n");
}

void install_signal_handlers() {
  Signal(SIGCHLD, sigchld_handler);
  Signal(SIGINT, sigint_handler);
  Signal(SIGTSTP, sigtstp_handler);
}