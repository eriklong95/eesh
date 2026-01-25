#include "../lib/job.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void test_register_jobs() {
  printf("*** test_register_jobs STARTED ***\n");

  struct JobList *jobs = NULL;

  pid_t pid = 13354;
  int bg = 1;
  register_job(&jobs, pid, bg);

  pid = 13355;
  bg = 1;
  register_job(&jobs, pid, bg);

  pid = 13356;
  bg = 1;
  register_job(&jobs, pid, bg);

  assert(jobs->head.pid == 13354);
  printf(" first job registered correctly\n");

  assert(jobs->tail->head.pid == 13355);
  printf(" second job registered correctly\n");

  assert(jobs->tail->tail->head.pid == 13356);
  printf(" third job registered correctly\n");

  printf("*** test_register_jobs PASSED ***\n");
}

void test_list_jobs() {
  printf("*** test_list_jobs STARTED ***\n");
  struct JobList *jobs = NULL;

  pid_t first_pid = 13340;
  int first_jid = register_job(&jobs, first_pid, 1);

  pid_t second_pid = 13341;
  int second_jid = register_job(&jobs, second_pid, 1);

  char *buffer = NULL;
  size_t size = 0;
  FILE *stream = open_memstream(&buffer, &size);

  write_job_list(jobs, stream);
  fclose(stream);

  char expected[1024];
  sprintf(expected, "Jobs:\n[JID] PID\n[%d] %d\n[%d] %d\n", first_jid,
          first_pid, second_jid, second_pid);

  assert(!strcmp(buffer, expected));

  free(buffer);

  printf("*** test_list_jobs PASSED ***\n");
}

int main() {
  test_register_jobs();
  test_list_jobs();
}