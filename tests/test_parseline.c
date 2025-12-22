#include <assert.h>
#include "eesh.h"

int main() {
  char *argv[8];
  int bg = parseline("ls\n", argv);

  assert(!bg);
  
}
