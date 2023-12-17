#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        // Error occurred during fork
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // This code is executed by the child process
        printf("Child Process: PID=%d\n", getpid());
    } else {
        // This code is executed by the parent process
        printf("Parent Process: PID=%d, Child PID=%d\n", getpid(), pid);
    }

    return 0;
}

