#include "lib/lib.h"
#include "lib/log.h"
#include "lib/sig.h"

int main() {
  eesh_log("-------------------\n");
  eesh_log("--- New session ---\n");
  eesh_log("-------------------\n");

  install_signal_handlers();
  run();
}
