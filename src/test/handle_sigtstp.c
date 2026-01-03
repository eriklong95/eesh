#include "../lib/csapp.h"
#include <stdio.h>
#include <unistd.h>

void handler(int sig) {
  Sio_puts("In the handler\n");
  _exit(0);
}

int main() {
  printf("(pid:%d) Hey, I am waiting for a SIGTSTP!\n", getpid());

  sigset_t mask, prev;

  Signal(SIGTSTP, handler);

  Pause();
  printf("We don't get here\n");
}