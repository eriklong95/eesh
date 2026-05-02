#include "../lib/csapp.h"
#include <bits/types/sigset_t.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
  Sio_puts("in handler");
  Sio_putl(sig);
  Sio_puts("\n");
}

int main() {
  Signal(SIGINT, handler);
  Signal(SIGUSR1, handler);
  sigset_t mask;
  Sigemptyset(&mask);
  Sigaddset(&mask, SIGUSR1);

  printf("will suspend (%d)\n", getpid());
  int rv = Sigsuspend(&mask);
  printf("after suspend, rv = %d\n", rv);
}