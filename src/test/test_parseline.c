#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/lib.h"

int main() {
  char *argv[] = { "asdf", "asdf" };
  char *buf = calloc(sizeof(char), 3);

  buf[0] = 'l';
  buf[1] = 's';
  buf[2] = '\n';
 
  int bg = parseline(buf, argv);

  assert(!bg);
  assert(!strcmp("ls", argv[0]));
  
}
