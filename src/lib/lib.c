#include "csapp.h"
#include "fg.h"
#include "input.h"
#include "job.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXARGS 128

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
  pid_t pid = Fork();
  if (pid == 0) {
    eesh_log("In child process, about to call execve\n");
    setpgid(getpid(), getpid());
    if (execve(argv[0], argv, environ) < 0) {
      printf("%s: Command not found.\n", argv[0]);
      exit(0);
    }
  } else {
    return pid;
  }
}

void evaluate(char *cmdline, struct JobList **jobs) {
  char *argv[MAXARGS];
  int bg;

  parse_input(cmdline, argv, &bg);

  eesh_log("Parsed input\n");

  if (argv[0] == NULL || builtin_command(argv, jobs)) {
    return;
  }

  eesh_log("Executing command\n");

  pid_t pid = execute(argv);

  if (!bg) {
    eesh_log("Running program as foreground process\n");
    set_fg_pgid(pid);
    int status;

    eesh_log("Will wait for process with PID %d to finish\n", pid);
    pid_t wait_rv = waitpid(pid, &status, WUNTRACED);
    eesh_log("Done waiting. Return value was %d\n", wait_rv);

    if (wait_rv < 0) {
      eesh_log("wait error\n");
      unix_error("waitfg: waitpid error");
    }

    if (WIFSTOPPED(status)) {
      eesh_log("Process with PID %d was stopped.\n", wait_rv);
    }
  } else {
    char *cmd = Calloc(strlen(cmdline), sizeof(char));
    strcpy(cmd, cmdline);
    int jid = register_job(jobs, cmd, pid);
    printf("[%d] %d %s", jid, pid, cmdline);
  }

  return;
}

void read_and_evaluate(char *cmdline, struct JobList **job_list) {
  printf(">");
  eesh_log("will read command line\n");
  Fgets(cmdline, MAXLINE, stdin);
  eesh_log("read completed\n");

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
    eesh_log("Before read_and_evaluate\n");
    read_and_evaluate(cmdline, job_list);
    eesh_log("After read_and_evaluate\n");
  }
}
