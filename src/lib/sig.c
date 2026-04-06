#include "csapp.h"
#include "fg.h"
#include "job.h"
#include "lib.h"
#include "log.h"
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
  eesh_log("Handling SIGINT\n");
  pid_t fg = get_fg_pgid();
  if (fg != 0) {
    eesh_log("Sending SIGINT to process group %d\n", fg);
    Kill(-fg, SIGINT);
    Sio_puts("\n");
  } else {
    Sio_puts("\n>");
  }
}

void sigtstp_handler(int sig) {
  eesh_log("Handling SIGTSTP\n");
  pid_t fg = get_fg_pgid();
  if (fg != 0) {
    eesh_log("Sending SIGTSTP to process group %d\n", fg);
    Kill(-fg, SIGTSTP);
    Sio_puts("Stopped ");
    Sio_putl(fg);
    Sio_puts("\n");
    // we actually need to put it in the job list here
    set_fg_pgid(0);
  }
}

void install_signal_handlers() {
  Signal(SIGCHLD, sigchld_handler);
  Signal(SIGINT, sigint_handler);
  Signal(SIGTSTP, sigtstp_handler);
}