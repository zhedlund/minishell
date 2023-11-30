#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */

int main(void)
{
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    char input[MAX_LINE];
    int i;

    while (should_run) {
        printf("minishell>");
        fflush(stdout);
        fgets(input, MAX_LINE, stdin);
        input[strlen(input) - 1] = '\0';
        if (strcmp(input, "exit") == 0) {
            should_run = 0;
            break;
        }
        char *token = strtok(input, " ");
        i = 0;
        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;
        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            printf("Command not found\n");
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            printf("Fork failed\n");
            exit(1);
        }
    }
    return 0;
}