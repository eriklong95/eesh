#include "../lib/job.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
  // init job list
  struct JobList jobs;

  printf("hello");

  // first job
  pid_t pid = 13354;
  int bg = 1;
  register_job(&jobs, pid, bg);

  // second job
  pid = 13355;
  bg = 1;
  register_job(&jobs, pid, bg);

  assert(jobs.head.pid == 13354);
  printf("first job registered correctly\n");

  assert(jobs.tail->head.pid == 13355);
  printf("second job registered correctly");
}