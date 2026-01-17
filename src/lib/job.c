#include "job.h"
#include <sys/types.h>

int register_job(struct JobList *jobs, pid_t pid, int bg) {
  struct Job job;
  job.pid = pid;
  job.bg = bg;
  job.jid = 1;

  append(jobs, job);

  return job.jid;
}

void append(struct JobList *jobs, struct Job job) {
  struct JobList end;
  end.head = job;
  end.tail = NULL;

  // find the end of the list
  struct JobList *p = jobs;
  while (p != NULL) {
    p = p->tail;
  }

  *p = end;
}