#include "csapp.h"
#include "fg.h"
#include "job.h"
#include "lib.h"
#include "log.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void child_terminated(pid_t pid, struct JobList **job_list) {
  if (pid == get_fg_pgid()) {
    set_fg_pgid(0);
  }
  remove_job(job_list, pid);
}

void child_exited(pid_t pid, int status, struct JobList **job_list) {
  eesh_log("Process with PID %d exited with exit code %d. The process has been "
           "reaped.\n",
           pid, WEXITSTATUS(status));
  child_terminated(pid, job_list);
}

void child_signaled(pid_t pid, int status, struct JobList **job_list) {
  eesh_log("Process with PID %d terminated because of uncaught signal %d. "
           "The process has been reaped.\n",
           pid, WTERMSIG(status));
  child_terminated(pid, job_list);
}

void fg_stopped(pid_t pid, struct JobList **job_list) {
  eesh_log(
      "Foreground process (PID=%d) stopped. Removing it as foreground job.\n",
      pid);
  set_fg_pgid(0);
  register_job(job_list, "", pid);
}

void child_stopped(pid_t pid, int status, struct JobList **job_list) {
  eesh_log("Process with PID %d was stopped by signal %d\n", pid,
           WSTOPSIG(status));
  pid_t fg_pgid = get_fg_pgid();
  if (pid == fg_pgid) {
    fg_stopped(pid, job_list);
  }
}

void sigchld_handler(int sig) {
  int olderrno = errno;
  pid_t pid = 0;
  struct JobList **job_list = jobs();

  eesh_log("Handling SIGCHLD.\n");

  int status;
  pid_t wait_set = -1;
  while ((pid = waitpid(wait_set, &status, WNOHANG | WUNTRACED)) > 0) {
    eesh_log("Waiting with wait set %d returned with %d.\n", wait_set, pid);
    if (WIFEXITED(status)) {
      child_exited(pid, status, job_list);
    } else if (WIFSIGNALED(status)) {
      child_signaled(pid, status, job_list);
    } else if (WIFSTOPPED(status)) {
      child_stopped(pid, status, job_list);
    } else {
      sio_error("unsupported status\n");
    }
  }

  if (!WIFSTOPPED(status) && errno != ECHILD) {
    eesh_log("errno = %d", errno);
    sio_error("waitpid error");
  } else {
    eesh_log("No more processes to wait for.\n", pid);
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
  }
}

void install_signal_handlers() {
  Signal(SIGCHLD, sigchld_handler);
  Signal(SIGINT, sigint_handler);
  Signal(SIGTSTP, sigtstp_handler);
}
