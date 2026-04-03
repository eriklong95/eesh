#include <stdarg.h>
#include <stdio.h>

FILE *log_file;

void init_log() { log_file = fopen("debug.log", "a"); }

void eesh_log(const char *restrict __format, ...) {
  va_list args;
  va_start(args, __format);
  vfprintf(log_file, __format, args);
  va_end(args);
  fflush(log_file);
}