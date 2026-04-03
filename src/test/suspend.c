#include "../lib/csapp.h"
#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

volatile sig_atomic_t flag = 0;

void handler(int sig) {
  Sio_puts("in handler: ");
  Sio_putl(sig);
  Sio_puts("\n");

  pid_t pid;
  int status;
  while ((pid = waitpid(flag, &status, 0)) > 0) {
    Sio_puts("Reaped process ");
    Sio_putl(pid);
    Sio_puts("\n");
    if (pid == flag) {
      Sio_puts("as expected\n");
      flag = 0;
    }

    if (WIFEXITED(status)) {
      Sio_puts("Process with PID ");
      Sio_putl(pid);
      Sio_puts(" exited with exit status ");
      Sio_putl(WEXITSTATUS(status));
      Sio_puts("\n");
    }
  }
}

int main(int argc, char *argv[], char *envp[]) {
  printf("Starting program\n");

  Signal(SIGCHLD, handler);
  printf("signal handler installed\n");

  sigset_t mask, prev;
  Sigemptyset(&mask);
  Sigaddset(&mask, SIGCHLD);

  Sigprocmask(SIG_BLOCK, &mask, &prev);
  printf("SIGCHLD blocked\n");
  pid_t pid;
  if ((pid = Fork()) == 0) {
    printf("in child\n");
    char *args[2];
    args[0] = "/usr/bin/sleep";
    args[1] = argv[1];
    execve("/usr/bin/sleep", args, envp);
  } else {
    flag = pid;
    // suspend until receipt of SIGCHLD
    printf("Waiting for child process to terminate\n");
    // why don't we hang here?
    while (flag != 0) {
      printf("flag = %d\n", flag);
      Sigsuspend(&prev);
    }
    printf("Done waiting\n");
    Sigprocmask(SIG_SETMASK, &prev, NULL);
  }
}