#include "lib/csapp.h"
#include "lib/lib.h"

int main() {
  char cmdline[MAXLINE];

  Signal(SIGINT, sigint_handler);
  Signal(SIGTSTP, sigtstp_handler);

  while (1) {
    printf(">");
    Fgets(cmdline, MAXLINE, stdin);

    if (feof(stdin)) {
      exit(0);
    }

    eval(cmdline);
  }

}
