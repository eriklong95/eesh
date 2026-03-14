#include "job.h"
#include <stdio.h>
#include <sys/types.h>

struct JobList *jobs = NULL;

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

int register_job_in_list(struct JobList **jobs, char *cmdline, pid_t pid,
                         int bg) {
  int jid = next_jid(*jobs);

  struct Job job;
  job.pid = pid;
  job.bg = bg;
  job.jid = jid;
  job.cmdline = cmdline;

  *jobs = append(*jobs, job);

  return job.jid;
}

int register_job(char *cmdline, pid_t pid, int bg) {
  return register_job_in_list(&jobs, cmdline, pid, bg);
}

void write_job_list(struct JobList *jobs, FILE *stream) {
  fprintf(stream, "Jobs:\n");
  fprintf(stream, "[JID] PID Command line\n");
  while (jobs != NULL) {
    fprintf(stream, "[%d] %d %s\n", jobs->head.jid, jobs->head.pid,
            jobs->head.cmdline);
    jobs = jobs->tail;
  }
}

void write_jobs(FILE *stream) { write_job_list(jobs, stream); }

struct JobList *remove_j(struct JobList *jobs, pid_t pid) {
  if (jobs->head.pid == pid) {
    return jobs->tail;
  } else {
    struct JobList *updated_tail = remove_j(jobs->tail, pid);
    jobs->tail = updated_tail;
    return jobs;
  }
}

void remove_job_from_list(struct JobList **jobs, pid_t pid) {
  *jobs = remove_j(*jobs, pid);
}

void remove_job(pid_t pid) { remove_job_from_list(&jobs, pid); }
