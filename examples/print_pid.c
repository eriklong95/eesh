#include <stdio.h>
#include <unistd.h>

int main() {
    
    int pid;

    while(getchar() != EOF) {
        pid = getpid();
        printf("PID is %d", pid);
    }
    


    return 0;
}