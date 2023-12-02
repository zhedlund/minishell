#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
//compile with -lreadline -lhistory

#define MAX_LINE 80 // Max command line length

char *ft_strtok(char *str, const char *delim);
int	ft_strcmp(const char *s1, const char *s2);

int main(void)
{
    char	*args[MAX_LINE]; // command line args
    int		i;
	char	*input;
	pid_t	pid;
	char	*token;

    while (1) 
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("\n");
			break ; // User pressed Ctrl+D or error
		}
		if (ft_strcmp(input, "exit") == 0) 
		{
			free(input);
			break ;
		}
		add_history(input); // Add input to the history
		token = ft_strtok(input, " \n");
		i = 0;
		while (token != NULL)
		{
			if (token[0] == '\"') // if space in folder name
			{
				char *closing_quote = strchr(token + 1, '\"');
				if (closing_quote != NULL)
				{
					closing_quote[0] = '\0'; //replace closing quote with null
					args[i] = token + 1; // Start from the character after the opening quote
				}
			}
			else
				args[i] = token;
			token = ft_strtok(NULL, " \n"); 
			i++;
		}
		args[i] = NULL;
		if (ft_strcmp(args[0], "cd") == 0) // works w "cd <dir>, "cd <dir>/<dir>", "cd ..", "cd ../../<dir>"
		{
			if (args[1] == NULL) 
			{
				if (chdir(getenv("HOME")) != 0) // cd w no args = home dir, chdir returns 0 on success
					perror("chdir");
			}
			else if (chdir(args[1]) != 0)
				perror("chdir");
			free(input); // Free input and continue loop
			continue ;
		}
		pid = fork();
		if (pid == 0)
		{
			execvp(args[0], args);
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
