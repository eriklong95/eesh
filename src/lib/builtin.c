#include "csapp.h"
#include "fg.h"
#include "job.h"
#include "log.h"
#include <sys/types.h>

void prepare_quit() { eesh_log("Quitting eesh ...\n"); }

void list_jobs(struct JobList *jobs) { write_jobs(jobs, stdout); }

void bg(char *arg, struct JobList *jobs) {
  int jid = atoi(arg);
  struct JobList *job_list = find_by_jid(jobs, jid);
  struct Job job = job_list->head;
  eesh_log("Sending SIGCONT to job %d (PID=%d).\n", jid, job.pid);
  Kill(-job.pid, SIGCONT);
}

void wait_for_fg_job() {
  sigset_t mask, prev;
  Sigemptyset(&mask);
  Sigaddset(&mask, SIGCHLD);
  Sigprocmask(SIG_BLOCK, &mask, &prev);
  while (get_fg_pgid() > 0) {
    eesh_log("(fg) Suspending to wait for signal.\n");
    Sigsuspend(&prev);
    eesh_log("(fg) Signal handled.\n");
  }
  Sigprocmask(SIG_SETMASK, &prev, NULL);
}

void fg(char *arg, struct JobList *jobs) {
  int jid = atoi(arg);
  struct JobList *job_list = find_by_jid(jobs, jid);
  struct Job job = job_list->head;

  pid_t pid = job.pid;
  eesh_log("Sending SIGCONT to job %d (PID=%d).\n", jid, pid);
  Kill(-pid, SIGCONT);
  // how to get it to the foreground?
  set_fg_pgid(pid);

  eesh_log("Job restarted to run in foreground. PID is %d. Waiting for it to "
           "stop or "
           "terminate.\n",
           pid);

  wait_for_fg_job();
  eesh_log("Done waiting.\n");
  // wait for the job to stop or terminate
  // react to signals sent by users
}