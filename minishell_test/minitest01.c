#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
//compile with -lreadline -lhistory

#define MAX_LINE 80 // Max command line length

int main(void)
{
    char *args[MAX_LINE]; // command line args
    int should_run = 1; // flag to determine when to exit 
    int i;
	char *input;

    while (should_run) 
	{
        input = readline("minishell> ");
        if (input == NULL) {
            printf("\n");
            break; // User pressed Ctrl+D or error
        }
        if (strcmp(input, "exit") == 0) 
		{
            should_run = 0;
            free(input);
            break;
		}
        add_history(input); // Add input to the history
        char *token = strtok(input, " ");
        i = 0;
        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " "); 
            i++;
        }
        args[i] = NULL;
		if (strcmp(args[0], "cd") == 0) 
		{
            if (args[1] == NULL) 
                printf("cd: missing argument\n");
			else if (chdir(args[1]) != 0) // returns 0 on success
                    perror("chdir");
			free(input); // Free input and continue loop
            continue;
		}
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
        free(input);
    }
    return (0);
}
