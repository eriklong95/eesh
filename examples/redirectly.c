#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    write(STDOUT_FILENO, "Hello and welcome!\n", 20);

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // The child process
        close(STDOUT_FILENO);

        printf("Can anybody hear me?\n");

        int fd;
        fd = open("./output.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        
        char *myargs[3];
        myargs[0] = strdup("ls");
        myargs[1] = strdup("-l");
        myargs[2] = NULL;

        execvp(myargs[0], myargs);
    } else {
        // The parent process
        int rc_wait = wait(NULL);
        printf("Where does this output go?\n");
    }
    return 0;
}
