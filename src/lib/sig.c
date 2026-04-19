#include "csapp.h"
#include "fg.h"
#include "job.h"
#include "lib.h"
#include "log.h"
#include <signal.h>
#include <stdlib.h>

void sigchld_handler(int sig) {
  int olderrno = errno;
  pid_t pid = 0;
  struct JobList **job_list = jobs();

  eesh_log("Handling SIGCHLD (pid=%d)\n", pid);

  int status;
  while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
    eesh_log("Reaped process with PID %d\n", pid);
    if (WIFEXITED(status)) {
      eesh_log("Process with PID %d exited with exit code %d\n", pid,
               WEXITSTATUS(status));
      remove_job(job_list, pid);
    } else if (WIFSIGNALED(status)) {
      eesh_log("Process with PID %d terminated because of uncaught signal %d\n",
               pid, WTERMSIG(status));
      remove_job(job_list, pid);
    } else if (WIFSTOPPED(status)) {
      eesh_log("Process with PID %d was stopped by signal %d\n", pid,
               WSTOPSIG(status));
    }
  }

  eesh_log("After while loop (pid=%d)\n", pid);

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