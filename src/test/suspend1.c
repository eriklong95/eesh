#include "../lib/csapp.h"
#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t flag = 0;

void handler(int sig) {
  Sio_puts("Received SIGCHLD\n");
  flag = 1;
}

void xhandler(int sig) {
  Sio_puts("Received signal ");
  Sio_putl(sig);
  Sio_puts("\n");
}

int main() {
  Signal(SIGCHLD, handler);
  Signal(SIGUSR1, xhandler);

  sigset_t mask, prev;
  Sigemptyset(&mask);
  Sigaddset(&mask, SIGCHLD);

  Sigprocmask(SIG_BLOCK, &mask, &prev);
  if (Fork() == 0) {
    Kill(getppid(), SIGUSR1);
    for (int i = 0; i < 5; i++) {
      printf("Doing work %d\n", i);
      sleep(1);
    }
  } else {
    printf("parent\n");
    while (flag == 0) {
      printf("suspending ... \n");
      Sigsuspend(&prev);
    }
    printf("After pause, flag = %d\n", flag);

    Sigprocmask(SIG_SETMASK, &prev, NULL);
  }
}