#include "../lib/csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void waitstatus(pid_t pid) {
  int status;
  pid_t rv;
  printf("will wait for process %d\n", pid);
  if ((rv = waitpid(pid, &status, WUNTRACED | WCONTINUED)) > 0) {
    printf("waitpid returned with value %d\n", rv);

    if (WIFEXITED(status)) {
      printf("process %d exited normally with status %d\n", rv,
             WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("process %d terminated on receipt of signal %d\n", rv,
             WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
      printf("process %d was stopped by signal %d\n", rv, WSTOPSIG(status));
    } else if (WIFCONTINUED(status)) {
      printf("process %d was restarted\n", rv);
    }

  } else {
    printf("waitpid error");
  }
}

int main() {
  pid_t pid = Fork();
  printf("after fork. %d\n", getpid());
  if (pid == 0) {
    int i = 0;
    while (1) {
      sleep(5);
      printf("doing stuff (%d)\n", i);
      i++;
    }
  } else {
    printf("pid = %d\n", pid);

    while (1) {
      waitstatus(pid);
    }
  }
}