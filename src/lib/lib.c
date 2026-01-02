#include "csapp.h"
#include <string.h>
#define MAXARGS 128

pid_t fg_pgid;

int parseline(char *buf, char **argv) {
  char *delim;
  int argc;
  int bg;

  unsigned long length = strlen(buf);
  *(buf + (length-1)) = ' ';
  while (*buf && (*buf == ' ')) {
    buf++;
  }

  argc = 0;
  while ((delim = strchr(buf, ' '))) {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;
  }

  argv[argc] = NULL;

  if (argc == 0) {
    return 1;
  }

  if ((bg = (*argv[argc-1] == '&') != 0)) {
    argv[--argc] = NULL;
  }

  return bg;

}

int builtin_command(char **argv) {
  if (!strcmp(argv[0], "quit")) {
    exit(0);
  }
  if (!strcmp(argv[0], "&")) {
    return 1;
  }
  return 0;
}

void sigint_handler(int sig) {
  if (fg_pgid != 0) {
    Kill(fg_pgid, SIGINT);
  }
  Sio_puts("\n");
}

void set_fg_pgid(pid_t pid) {
  fg_pgid = pid;
}

void prepare(char *cmdline, char **argv, int *bg) {
  char buf[MAXLINE];
  strcpy(buf, cmdline);
  *bg = parseline(buf, argv);
}

void exec(char **argv) {
  setpgid(getpid(), getpid());
  if (execve(argv[0], argv, environ) < 0) {
    printf("%s: Command not found.\n", argv[0]);
    exit(0);
  }
}

void eval(char *cmdline) {
  char *argv[MAXARGS];
  int bg;
  pid_t pid;

  prepare(cmdline, argv, &bg);

  if (argv[0] == NULL) {
    return;
  }

  if (!builtin_command(argv)) {
    if ((pid = Fork()) == 0) {
      exec(argv);
    }

    if (!bg) {
      set_fg_pgid(pid);
      int status;
      if (waitpid(pid, &status, 0) < 0) {
        unix_error("waitfg: waitpid error");
      }
    } else {
      printf("%d %s", pid, cmdline);
    }
  }
  return;
}
