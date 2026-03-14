#include "lib/csapp.h"
#include "lib/lib.h"

int main() {
  char cmdline[MAXLINE];

  install_signal_handlers();

  while (1) {
    read_and_evaluate(cmdline);
  }
}
