#include "../lib/csapp.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) {
  Sio_puts("In the handler\n");
  _exit(0);
}

int main() {
  printf("Hey, I am waiting for a SIGINT!\n");

  sigset_t mask, prev;

  Signal(SIGINT, handler);

  Pause();

  printf("We don't get here\n");
}