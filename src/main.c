#include "lib/csapp.h"
#include "lib/lib.h"

int main() {
  char cmdline[MAXLINE];

  while (1) {
    printf(">");
    Fgets(cmdline, MAXLINE, stdin);

    if (feof(stdin)) {
      exit(0);
    }

    eval(cmdline);
  }
  
}

