#include <stdio.h>
#include <stdlib.h>

#include "include/user_input.h"

int main()
{
	char input[1000];

	printf("eesh/> ");
	fgets(input, 100, stdin);

	CommandLine *cli;
	cli = parse(input);

	printf("unknown command: %s\n", cli->executable);

	return 0;
}
