#include <stdio.h>
#include <unistd.h>

/*
  Prints a number each second.
*/
int main() {
  int counter = 0;

  while (counter < 10) {
    sleep(1);
    printf("counter = %d\n", counter);
    counter++;
  }
}