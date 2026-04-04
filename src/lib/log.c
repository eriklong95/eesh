#include "csapp.h"
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void eesh_log(const char *restrict __format, ...) {
  int log_fd = Open("debug.log", O_WRONLY | O_APPEND | O_CREAT,
                    S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP |
                        S_IROTH | S_IXOTH | S_IWOTH);
  char log_line[MAXLINE];
  char log_message[MAXLINE - 128];

  va_list args;
  va_start(args, __format);
  vsprintf(log_message, __format, args);
  va_end(args);

  sprintf(log_line, "[%d] %s", getpid(), log_message);
  Write(log_fd, log_line, strlen(log_line));
  Close(log_fd);
}