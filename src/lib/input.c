#include "csapp.h"
#include <string.h>

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

void parse_input(char *cmdline, char **argv, int *bg) {
  char buf[MAXLINE];
  strcpy(buf, cmdline);
  *bg = parseline(buf, argv);
}