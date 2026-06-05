#include "csapp.h"
#include "fg.h"
#include "input.h"
#include "job.h"
#include "log.h"
#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXARGS 128
#include "sig.h"

int builtin_command(char **argv, struct JobList **jobs) {
  if (!strcmp(argv[0], "quit")) {
    eesh_log("Quitting eesh ...\n");
    exit(0);
  } else if (!strcmp(argv[0], "jobs")) {
    write_jobs(*jobs, stdout);
    return 1;
  }
  return 0;
}

pid_t execute(char **argv) {
  eesh_log("Forking child process to run program.\n");
  pid_t pid = Fork();
  if (pid == 0) {
    pid_t child_pid = getpid();
    eesh_log("This process was forked to run program. Setting process group ID "
             "to %d.\n",
             child_pid);
    setpgid(child_pid, child_pid);
    eesh_log("Calling execve to run program in this process.\n");
    if (execve(argv[0], argv, environ) < 0) {
      printf("%s: Command not found.\n", argv[0]);
      exit(0);
    }
  } else {
    eesh_log("Process with PID %d forked from this process to run program.\n",
             pid);
    return pid;
  }
}

void evaluate(char *cmdline, struct JobList **jobs) {
  char *argv[MAXARGS];
  int bg;

  parse_input(cmdline, argv, &bg);

  if (argv[0] == NULL || builtin_command(argv, jobs)) {
    return;
  }

  eesh_log("Executing command.\n");

  sigset_t mask, prev;
  Sigemptyset(&mask);
  Sigaddset(&mask, SIGCHLD);

  Sigprocmask(SIG_BLOCK, &mask, &prev);
  pid_t pid = execute(argv);

  if (!bg) {
    eesh_log("Running program as foreground process.\n");
    set_fg_pgid(pid);
    int status;

    eesh_log("Waiting for process with PID %d to stop or terminate.\n", pid);

    while (get_fg_pgid() > 0) { // wait for foreground job to stop or terminate
      eesh_log("Suspending to wait for signal.\n");
      Sigsuspend(&prev);
      eesh_log("Signal handled.\n");
    }
    Sigprocmask(SIG_SETMASK, &prev, NULL);
    eesh_log("Done waiting.\n");

  } else {
    Sigprocmask(SIG_SETMASK, &prev, NULL);
    char *cmd = Calloc(strlen(cmdline), sizeof(char));
    strcpy(cmd, cmdline);
    int jid = register_job(jobs, cmd, pid);
    printf("[%d] %d %s", jid, pid, cmdline);
  }

  return;
}

void read_and_evaluate(char *cmdline, struct JobList **job_list) {
  printf(">");

  eesh_log("Reading command.\n");
  Fgets(cmdline, MAXLINE, stdin);

  size_t length = strlen(cmdline);
  char cli[MAXLINE];
  strncpy(cli, cmdline, length - 1);
  eesh_log("Read command `%s`\n", cli);

  if (feof(stdin)) {
    exit(0);
  }

  evaluate(cmdline, job_list);
}

void run() {
  char cmdline[MAXLINE];
  struct JobList **job_list = jobs();

  while (1) {
    read_and_evaluate(cmdline, job_list);
    eesh_log("Done processing command.\n");
  }
}
