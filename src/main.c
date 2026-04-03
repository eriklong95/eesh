#include "lib/lib.h"
#include "lib/log.h"
#include "lib/sig.h"

int main() {
  eesh_log_new_session();
  install_signal_handlers();
  run();
}
