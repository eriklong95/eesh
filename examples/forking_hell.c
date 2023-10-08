#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf("Welcome! (pid:%d)\n", (int)getpid());

	int rc = fork();

	if (rc < 0)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (rc == 0)
	{
		printf("Hello! Here rc = %d and pid = %d.\n", (int)rc, (int)getpid());
	}
	else
	{
		sleep(5);
		printf("Hello! Here rc = %d and pid = %d\n", (int)rc, (int)getpid());
	}
	return 0;
}
