#include <stdio.h>

int main() {
	char *line;

	printf("eesh/> ");
	fgets(line, 100, stdin);
	printf("%s", line);
	printf("eesh/>\n");

	return 0;
}

