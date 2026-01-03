#include "csapp.h"
#include <string.h>
#define MAXARGS 128

pid_t fg_pgid; // volatile ??

int parseline(char *buf, char **argv) {
  char *delim;
  int argc;
  int bg;

  unsigned long length = strlen(buf);
  *(buf + (length - 1)) = ' ';
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

  if ((bg = (*argv[argc - 1] == '&') != 0)) {
    argv[--argc] = NULL;
  }

  return bg;
}

int builtin_command(char **argv) {
  if (!strcmp(argv[0], "quit")) {
    exit(0);
  }
  return 0;
}

void sigint_handler(int sig) {
  if (fg_pgid != 0) {
    Kill(-fg_pgid, SIGINT);
  }
  Sio_puts("\n");
}

void sigtstp_handler(int sig) {
  Sio_puts("in SIGTSTP handler\n");
  if (fg_pgid != 0) {
    Sio_puts("fg_pgid is ");
    Sio_putl(fg_pgid);
    Sio_puts("\n");
    Kill(-fg_pgid, SIGTSTP);
    Sio_puts("Stopped");
  }
  Sio_puts("\n");
}

void set_fg_pgid(pid_t pid) { fg_pgid = pid; }

void prepare(char *cmdline, char **argv, int *bg) {
  char buf[MAXLINE];
  strcpy(buf, cmdline);
  *bg = parseline(buf, argv);
}

pid_t exec(char **argv) {
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

void eval(char *cmdline) {
  char *argv[MAXARGS];
  int bg;

  prepare(cmdline, argv, &bg);

  if (argv[0] == NULL || builtin_command(argv)) {
    return;
  }

  pid_t pid = exec(argv);

  if (!bg) {
    set_fg_pgid(pid);
    int status;
    if (waitpid(pid, &status, 0) < 0) {
      unix_error("waitfg: waitpid error");
    }
  } else {
    printf("%d %s", pid, cmdline);
  }

  return;
}
