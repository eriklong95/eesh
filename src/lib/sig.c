#include "csapp.h"
#include "fg.h"
#include <signal.h>

void sigchld_handler(int sig) { Sio_puts("A child stopped or terminated"); }

void sigint_handler(int sig) {
  pid_t fg = get_fg_pgid();
  if (fg != 0) {
    Kill(-fg, SIGINT);
  }
  Sio_puts("\n");
}

void sigtstp_handler(int sig) {
  pid_t fg = get_fg_pgid();
  if (fg != 0) {
    Kill(-fg, SIGTSTP);
    Sio_puts("Stopped ");
    Sio_putl(fg);
    Sio_puts("\n");
    set_fg_pgid(0);
  }
  Sio_puts("\n");
}

void install_signal_handlers() {
  Signal(SIGCHLD, sigchld_handler);
  Signal(SIGINT, sigint_handler);
  Signal(SIGTSTP, sigtstp_handler);
}