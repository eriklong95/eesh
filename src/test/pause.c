#include "../lib/csapp.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) {
  Sio_puts("Received signal ");
  Sio_putl(sig);
  Sio_puts("\n");
}

int main() {
  Signal(SIGUSR1, handler);

  if (Fork() == 0) {
    printf("will send SIGUSR1 to parent\n");
    Kill(getppid(), SIGUSR1);
  } else {
    printf("parent\n");
    Pause();
    printf("After pause\n");
  }
}