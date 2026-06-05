#include "csapp.h"
#include "fg.h"
#include "job.h"
#include "lib.h"
#include "log.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile sig_atomic_t child_reaped;

sig_atomic_t get_child_reaped() {
  eesh_log("getting child_reaped value = %d\n", child_reaped);
  return child_reaped;
}

void set_child_reaped(sig_atomic_t value) {
  eesh_log("setting child_repead = %d\n", value);
  child_reaped = value;
}

int fg_stopped(int sig) {
  int status;
  pid_t fg_pid = get_fg_pgid();
  eesh_log("checking if foreground job %d was stopped\n", fg_pid);

  pid_t pid = waitpid(fg_pid, &status, WNOHANG | WUNTRACED);
  if (pid > 0) {
    if (WIFSTOPPED(status)) {
      eesh_log("Process with PID %d was stopped by signal %d\n", pid,
               WSTOPSIG(status));
      return 1;
    } else {
      eesh_log("Waitpid returned with %d but not stopped\n", pid);
      return 0;
    }
  } else if (pid == 0) {
    eesh_log("No child has stopped or terminated\n");
    return 0;
  } else {
    sio_error("waitpid error");
    return 0;
  }
}

void sigchld_handler(int sig) {
  int olderrno = errno;
  pid_t pid = 0;
  struct JobList **job_list = jobs();

  eesh_log("Handling SIGCHLD\n");

  if (fg_stopped(sig)) {
    set_child_reaped(1);
    return;
  }

  int status;
  while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
    set_child_reaped(1);
    eesh_log("Waitpid returned with %d\n", pid);
    if (WIFEXITED(status)) {
      eesh_log("Process with PID %d exited with exit code %d. Reaped\n", pid,
               WEXITSTATUS(status));
      remove_job(job_list, pid);
    } else if (WIFSIGNALED(status)) {
      eesh_log("Process with PID %d terminated because of uncaught signal %d. "
               "Reaped\n",
               pid, WTERMSIG(status));
      remove_job(job_list, pid);
    } else if (WIFSTOPPED(status)) {
      eesh_log("Process with PID %d was stopped by signal %d\n", pid,
               WSTOPSIG(status));
    }
  }

  eesh_log("After while loop (pid=%d)\n", pid);

  if (errno != ECHILD) {
    eesh_log("errno = %d", errno);
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
  }
}

void install_signal_handlers() {
  Signal(SIGCHLD, sigchld_handler);
  Signal(SIGINT, sigint_handler);
  Signal(SIGTSTP, sigtstp_handler);
}
