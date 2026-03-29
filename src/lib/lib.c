#include "csapp.h"
#include "fg.h"
#include "input.h"
#include "job.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXARGS 128

int builtin_command(char **argv, struct JobList **jobs) {
  if (!strcmp(argv[0], "quit")) {
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

  if (argv[0] == NULL || builtin_command(argv, jobs)) {
    return;
  }

  pid_t pid = execute(argv);

  if (!bg) {
    set_fg_pgid(pid);
    int status;
    if (waitpid(pid, &status, WUNTRACED) < 0) {
      unix_error("waitfg: waitpid error");
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
  Fgets(cmdline, MAXLINE, stdin);

  if (feof(stdin)) {
    exit(0);
  }

  evaluate(cmdline, job_list);
}
