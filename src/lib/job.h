#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

struct Job {
  pid_t pid; // the process group ID for the job
  int jid;   // job ID, small positive integer
  int bg;    // is the job running in the background
};

// a linked list of jobs
struct JobList {
  struct Job head;
  struct JobList *tail;
};

void append(struct JobList **, struct Job);

int register_job(struct JobList **, pid_t, int);
