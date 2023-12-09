#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_LINE 80 // Max command line length

char *ft_strtok(char *str, const char *delim);
int ft_strcmp(const char *s1, const char *s2);
int ft_execvp(const char *file, char *const argv[]);

int main(void) {
    char *args[MAX_LINE]; // command line args
    int i;
    char *input;
    pid_t pid;

    while (1) {
        input = readline("minishell> ");
        if (input == NULL) {
            printf("\n");
            break; // User pressed Ctrl+D or error
        }
        if (ft_strcmp(input, "exit") == 0) {
            free(input);
            break;
        }
        add_history(input); // Add input to the history

        char *token = ft_strtok(input, " \n");
        i = 0;

        while (token != NULL) {
            args[i] = token;
            token = ft_strtok(NULL, "\n"); // Read until end of line for the 'cd' command
            i++;
        }
        args[i] = NULL;

        if (ft_strcmp(args[0], "cd") == 0) {
            char dir[MAX_LINE] = "";
            for (int j = 1; args[j] != NULL; ++j) {
                strcat(dir, args[j]);
                if (args[j + 1] != NULL) strcat(dir, " "); // Add space if there are more arguments
            }
            if (chdir(dir) != 0)
                perror("chdir");
            free(input); // Free input and continue loop
            continue;
        }
		pid = fork();
        if (pid == 0)
		{
			ft_execvp(args[0], args);
			printf("Command not found\n");
			exit(1);
        }
        else if (pid > 0)
            wait(NULL);
        else
		{
            perror("pid");
            exit(1);
        }

        free(input);
    }
    return (0);
}