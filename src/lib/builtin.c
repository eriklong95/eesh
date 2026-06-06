#include "csapp.h"
#include "job.h"
#include "log.h"

void prepare_quit() { eesh_log("Quitting eesh ...\n"); }

void list_jobs(struct JobList *jobs) { write_jobs(jobs, stdout); }

void bg(char *arg, struct JobList *jobs) {
  int jid = atoi(arg);
  struct JobList *job_list = find_by_jid(jobs, jid);
  struct Job job = job_list->head;
  eesh_log("Sending SIGCONT to job %d (PID=%d).\n", jid, job.pid);
  Kill(-job.pid, SIGCONT);
}