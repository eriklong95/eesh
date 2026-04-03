#include "../lib/log.h"
#include <unistd.h>

int main() {
  int counter = 0;

  while (1) {
    sleep(1);
    eesh_log("counter = %d\n", counter);
    counter++;
  }
}