#include "job.h"
#include <stdio.h>
#include <sys/types.h>

struct JobList *append(struct JobList *jobs, struct Job job) {
  if (jobs == NULL) {
    struct JobList *end = malloc(sizeof(struct JobList));
    end->head = job;
    end->tail = NULL;
    return end;
  } else {
    jobs->tail = append(jobs->tail, job);

    return jobs;
  }
}

int register_job(struct JobList **jobs, pid_t pid, int bg) {
  struct Job job;
  job.pid = pid;
  job.bg = bg;
  job.jid = 1;

  *jobs = append(*jobs, job);

  return job.jid;
}

void write_job_list(struct JobList *jobs, FILE *stream) {
  fprintf(stream, "Jobs:\n");
  fprintf(stream, "[JID] PID\n");
  while (jobs != NULL) {
    fprintf(stream, "[%d] %d\n", jobs->head.jid, jobs->head.pid);
    jobs = jobs->tail;
  }
}
