#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sigchld_handler(int signum) {
    int status;
    pid_t pid;
    
    // Loop to reap all terminated child processes
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Process %d exited with status %d\n", pid, exit_status);
        }
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    // Create child process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) { // Child process
        // Create grandchild process
        pid_t gpid = fork();
        if (gpid == -1) {
            perror("fork");
            exit(1);
        } else if (gpid == 0) { // Grandchild process
            // Do grandchild process work
            printf("Grandchild process doing work...\n");
            exit(42); // Exit with a status code
        } else { // Child process
            printf("Child process waiting for grandchild...\n");
            // Child process continues executing while waiting for grandchild to terminate
            waitpid(gpid, NULL, 0);
            printf("Child process exiting...\n");
            exit(0);
        }
    } else { // Parent process
        printf("Parent process waiting for child...\n");
        // Parent process continues executing while waiting for child to terminate
        waitpid(pid, NULL, 0);
        printf("Parent process exiting...\n");
    }

    return 0;
}
