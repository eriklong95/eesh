#include <signal.h>
void install_signal_handlers();

sig_atomic_t get_child_reaped();
void set_child_reaped(sig_atomic_t value);