#include "../lib/job.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void test_remove_job() {
  printf("*** test_remove_job STARTED ***\n");

  struct JobList *jobs = NULL;

  remove_job_from_list(&jobs, 13354);
  printf("removing from empty list works\n");

  pid_t pid = 13354;
  int bg = 1;
  register_job_in_list(&jobs, "/usr/bin/ps", pid, bg);

  pid = 13355;
  bg = 1;
  register_job_in_list(&jobs, "/usr/bin/ps", pid, bg);

  remove_job_from_list(&jobs, 13354);

  assert(jobs->head.pid == 13355);
  printf("job was removed\n");

  printf("*** test_register_jobs PASSED ***\n");
}

void test_register_jobs() {
  printf("*** test_register_jobs STARTED ***\n");

  struct JobList *jobs = NULL;

  pid_t pid = 13354;
  int bg = 1;
  register_job_in_list(&jobs, "/usr/bin/ps", pid, bg);

  pid = 13355;
  bg = 1;
  register_job_in_list(&jobs, "/usr/bin/ps", pid, bg);

  pid = 13356;
  bg = 1;
  register_job_in_list(&jobs, "/usr/bin/ps", pid, bg);

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
  int first_jid = register_job_in_list(&jobs, "/usr/bin/ps", first_pid, 1);

  pid_t second_pid = 13341;
  int second_jid = register_job_in_list(&jobs, "/usr/bin/ps", second_pid, 1);

  char *buffer = NULL;
  size_t size = 0;
  FILE *stream = open_memstream(&buffer, &size);

  write_job_list(jobs, stream);
  fclose(stream);

  char expected[1024];
  sprintf(expected, "Jobs:\n[JID] PID Command line\n[%d] %d %s\n[%d] %d %s\n",
          first_jid, first_pid, "/usr/bin/ps", second_jid, second_pid,
          "/usr/bin/ps");

  assert(!strcmp(buffer, expected));

  free(buffer);

  printf("*** test_list_jobs PASSED ***\n");
}

void test_jids() {
  printf("*** test_jids STARTED ***\n");
  struct JobList *jobs = NULL;

  pid_t first_pid = 13420;
  int first_jid = register_job_in_list(&jobs, "/usr/bin/ps", first_pid, 1);
  assert(first_jid == 1);

  pid_t second_pid = 13421;
  int second_jid = register_job_in_list(&jobs, "/usr/bin/ps", second_pid, 1);
  assert(second_jid == 2);

  printf("*** test_jids PASSED ***\n");
}

int main() {
  test_remove_job();
  test_register_jobs();
  test_list_jobs();
  test_jids();
}