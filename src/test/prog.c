#include <unistd.h>
#include <stdio.h>

int main() {
  pid_t pid;

  if ((pid = fork()) == 0) {
    while (1) {
      sleep(1);
      printf("(child) I am still here\n");
    }
  }

  while (1) {
    sleep(1);
    printf("(parent) I am still here\n");
  }
}