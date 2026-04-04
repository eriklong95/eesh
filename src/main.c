#include "lib/lib.h"
#include "lib/sig.h"

int main() {
  install_signal_handlers();
  run();
}
