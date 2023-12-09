#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

char **tokenizer(char *input);
void parser(char **tokens);
void execute_command(char **command);

int main(void)
{
    char *input;
    char **tokens;

    while (1)
	{
        input = readline("minishell> ");
        if (input == NULL)
		{
            printf("\n");
            break; // User pressed Ctrl+D or error
        }
        // Tokenizing input
        tokens = tokenizer(input);
        // Parsing tokens
        parser(tokens);
        // Executing parsed command
        executeCommand(tokens);
        free(input);
        free(tokens);
    }
    return (0);
}