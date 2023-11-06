#include <stdio.h>
#include <unistd.h>

int main() {
    
    int pid;

    pid = getpid();

    while(1) {
        sleep(1);
        printf("PID is %d\n", pid);
    }
    
    return 0;
}