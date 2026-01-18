#include "job.h"
#include <stdio.h>
#include <sys/types.h>

int register_job(struct JobList **jobs, pid_t pid, int bg) {
  struct Job job;
  job.pid = pid;
  job.bg = bg;
  job.jid = 1;

  append(jobs, job);

  return job.jid;
}

void append(struct JobList **jobs, struct Job job) {
  struct JobList *end = malloc(sizeof(struct JobList));
  end->head = job;
  end->tail = NULL;

  if (*jobs == NULL) {
    // the list is empty
    // insert new element as first one
    *jobs = end;
  } else if ((*jobs)->tail == NULL) {
    // the list has only one element
    // insert new element as second one
    (*jobs)->tail = end;
  }
}