#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	printf("Hello world (pid:%d)\n", (int)getpid());

	int rc = fork();

	if (rc < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (rc == 0)
	{
		// child process
		int child_pid;
		child_pid = getpid();
		printf("Hello, I am the child process (pid:%d)\n", child_pid);

		char *myargs[3];
		myargs[0] = strdup("wc");
		myargs[1] = strdup("README.md");
		myargs[2] = NULL;

		execvp(myargs[0], myargs);
		printf("Will this print statement be executed?");
	}
	else
	{
		// parent process
		int rc_wait = wait(NULL);
		printf("Hello, I am the parent process of %d (rc_wait: %d) (pid:%d)\n", rc, rc_wait, (int)getpid());
	}
	return 0;
}
