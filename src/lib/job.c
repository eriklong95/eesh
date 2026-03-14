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

int next_jid(struct JobList *jobs) {
  int jid = 0;
  while (jobs != NULL) {
    if (jobs->head.jid > jid) {
      jid = jobs->head.jid;
    }
    jobs = jobs->tail;
  }

  return jid + 1;
}

int register_job(struct JobList **jobs, pid_t pid, int bg) {
  int jid = next_jid(*jobs);

  struct Job job;
  job.pid = pid;
  job.bg = bg;
  job.jid = jid;

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

struct JobList *remove_j(struct JobList *jobs, pid_t pid) {
  if (jobs->head.pid == pid) {
    return jobs->tail;
  } else {
    struct JobList *updated_tail = remove_j(jobs->tail, pid);
    jobs->tail = updated_tail;
    return jobs;
  }
}

int remove_job(struct JobList **jobs, pid_t pid) {
  *jobs = remove_j(*jobs, pid);
}
