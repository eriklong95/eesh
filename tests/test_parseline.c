#include <assert.h>
#include "../src/lib.h"

int main() {
  char *argv[8];
  int bg = parseline("ls\n", argv);

  assert(!bg);
  
}
