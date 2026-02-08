#include "csapp.h"
#include "input.h"
#include "job.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXARGS 128

pid_t fg_pgid; // volatile ??

pid_t get_fg_pgid() { return fg_pgid; }

void set_fg_pgid(pid_t pid) { fg_pgid = pid; }

int builtin_command(char **argv, struct JobList *jobs) {
  if (!strcmp(argv[0], "quit")) {
    exit(0);
  } else if (!strcmp(argv[0], "jobs")) {
    write_job_list(jobs, stdout);
    return 1;
  }
  return 0;
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
  Signal(SIGINT, sigint_handler);
  Signal(SIGTSTP, sigtstp_handler);
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

  if (argv[0] == NULL || builtin_command(argv, *jobs)) {
    return;
  }

  pid_t pid = execute(argv);
  int jid = register_job(jobs, pid, bg);

  if (!bg) {
    set_fg_pgid(pid);
    int status;
    if (waitpid(pid, &status, WUNTRACED) < 0) {
      unix_error("waitfg: waitpid error");
    }
  } else {
    printf("[%d] %d %s", jid, pid, cmdline);
  }

  return;
}

void read_and_evaluate(char *cmdline, struct JobList **jobs) {
  printf(">");
  Fgets(cmdline, MAXLINE, stdin);

  if (feof(stdin)) {
    exit(0);
  }

  evaluate(cmdline, jobs);
}
