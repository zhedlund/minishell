/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:07:54 by zhedlund          #+#    #+#             */
/*   Updated: 2023/12/10 19:20:30 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_TOKENS 64
#define MAX_TOKEN_LEN 128


/* Function to check if command is a built-in command
 * @param command: command to check
 * @return: 1 if command is a built-in command, 0 if not
*/
int is_builtin(char *command)
{
    char	*builtin_cmd[4];
    int		num_cmd;
	int		i;

	builtin_cmd[0] = "cd";
	builtin_cmd[1] = "exit";
	builtin_cmd[2] = "export";
	builtin_cmd[3] = "unset";
	num_cmd = sizeof(builtin_cmd) / sizeof(builtin_cmd[0]); // total size of array / size of one element = number of elements in array
	i = 0;
	while (i < num_cmd)
	{
		if (ft_strncmp(command, builtin_cmd[i], sizeof(builtin_cmd)) == 0)
			return (1); // Command is a built-in command
		i++;
	}
    return (0); // Command is not a built-in command
}

/* Function to parse the command type
 * @param tokens: array of tokens
 * @return: command type
 */
int parse_cmd_type(char **tokens)
{
	int	i;

    if (tokens[0] != NULL)
	{
		if (is_builtin(tokens[0]))
			return (0); // Process as a built-in command
		else if (ft_strcmp(tokens[0], "|") == 0)
            return (1); // Process as a piped command
		else if ((ft_strcmp(tokens[0], ">") == 0 || strcmp(tokens[0], ">>") == 0
			|| ft_strcmp(tokens[0], "<") == 0) || strcmp(tokens[0], "<<") == 0)
			return (2); // Process as a redirection command
		else if (ft_strcmp(tokens[0], "$") == 0)
			return (3); // Process as expansion
		else
			printf("command not found\n");
    }
	i = 0;
	while (i < MAX_TOKENS)
		free(tokens[i++]); // Free memory allocated for tokens
    free(tokens);
	return (-1); // No command was entered
}

/* main to test parser */
int main(int argc, char *argv[])
{
    if (argc < 2)
	{
        printf("%s\n", argv[0]);
        return (1);
    }
    char *input = argv[1];
    const char delimiters[] = " \t\n"; // Delimiters: space, tab, newline
    char **tokens = tokenizer(input, delimiters); // Tokenize input
    int execflag = parse_cmd_type(tokens); // Identify command type
	if (execflag == 0)
		printf("Parsed command is a built-in command.\n"); // Process as a built-in command
		//execute_builtin(tokens);
	if (execflag == 1)
		printf("Parsed command is a piped command.\n"); // Process as a piped command
		//execute_piped(tokens);
	if (execflag == 2)
		printf("Parsed command is a redirection > >> << <\n"); 
		//execute_redirection(tokens);
	if (execflag == 3)
		printf("Parsed command is expansion command\n");
		//execute_expansion(tokens);
    return (0);
}