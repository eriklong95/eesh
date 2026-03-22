#include "job.h"
#include <stdio.h>
#include <sys/types.h>

struct JobList *job_list = NULL;

struct JobList **jobs() { return &job_list; }

void append(struct JobList **jobs, struct Job job) {
  if (*jobs == NULL) {
    struct JobList *end = malloc(sizeof(struct JobList));
    end->head = job;
    end->tail = NULL;
    *jobs = end;
  } else {
    append(&((*jobs)->tail), job);
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

int register_job(struct JobList **jobs, char *cmdline, pid_t pid) {
  int jid = next_jid(*jobs);

  struct Job job;
  job.pid = pid;
  job.jid = jid;
  job.cmdline = cmdline;

  append(jobs, job);

  return job.jid;
}

void write_jobs(struct JobList *jobs, FILE *stream) {
  fprintf(stream, "Jobs:\n");
  fprintf(stream, "[JID] PID Command line\n");
  while (jobs != NULL) {
    fprintf(stream, "[%d] %d %s\n", jobs->head.jid, jobs->head.pid,
            jobs->head.cmdline);
    jobs = jobs->tail;
  }
}

void remove_job(struct JobList **jobs, pid_t pid) {
  if (*jobs == NULL) {
    return;
  } else if ((*jobs)->head.pid == pid) {
    *jobs = (*jobs)->tail;
  } else {
    struct JobList **tail = &(*jobs)->tail;
    remove_job(tail, pid);
  }
}
