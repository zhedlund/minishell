#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "Builtins.h"
//compile with -lreadline -lhistory
#define MAX_LINE 80 // Max command line length

void	ft_ctrlc(int sig)
{
    if (sig == SIGINT)
    {
        write(STDERR_FILENO, "\n", 1);
        rl_replace_line("\0", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

int main(int argc, char **argv)
{
    char *args[MAX_LINE]; // command line args
    int should_run = 1; // flag to determine when to exit
    int i;
    char *inputt;
    char **commands;
    char *commandline;
    int	pid;
    int	status;
    t_info	*info;
    
    commands = NULL;
while (should_run)
{
	info = NULL;
	info = ft_calloc(sizeof(t_info), 1);
	signal(SIGINT, ft_ctrlc);
        info->input = readline("minishell> ");
        //inputt = readline("minishell> ");
        if (info->input == NULL) {
            printf("\n");
            break; // User pressed Ctrl+D or error
        }
        if (strcmp(info->input, "exit") == 0)
        {
            should_run = 0;
            free(info->oldpwd);
            free(info->input);
            free(info);
            break;
        }
        add_history(info->input); // Add input to the history
        //char *token = strtok(input, " ");
        //i = 0;
        //while (token != NULL) {
         //   args[i] = token;
          //  token = strtok(NULL, " ");
          //  i++;
        //}
        //args[i] = NULL;
        //if ((pid = fork()) == 0)
        ft_inputs(ft_strdup(info->input, 0), &info);
	//waitpid(pid, &status, 0);
	//ft_freearray(info->inputs);
        //free(input);
       /* pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args); //important
            printf("Command not found\n");
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            printf("Fork failed\n");
            exit(1);
        }*/
        free(info->input);
    	free(info);
    }
    return (0);
}
