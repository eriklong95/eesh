#include "../lib/job.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
  struct JobList *jobs = NULL;

  pid_t pid = 13354;
  int bg = 1;
  register_job(jobs, pid, bg);

  assert(jobs->head.pid == 13354);
  printf("first job registered correctly\n");
}