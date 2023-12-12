/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:55:10 by zhedlund          #+#    #+#             */
/*   Updated: 2023/12/12 23:15:18 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to expand environment variables in tokens
* @param tokens: array of tokens
* @return: void
*/
void expand_variables(char **tokens)
{
    int i = 0;
    while (tokens[i] != NULL)
	{
        if (tokens[i][0] == '$')
		{
            char *variable_name = tokens[i] + 1; // Skip the '$' character
            char *value = getenv(variable_name);
            if (value != NULL)
			{
                free(tokens[i]);
                tokens[i] = ft_strdup(value); // Replace token with variable's value
            }
			else
			{
                printf("Variable %s not found in the environment.\n", variable_name);
				// TODO check how handled in bash
            }
        }
        i++;
    }
}


/* main function to test expand_variables */
int main()
{
    // Simulating setting environment variables
    //setenv("SHELL", "/bin/bash", 1);
    char input[] = "$USER $SHELL $HOME"; // Simulating user input
    const char delimiters[] = " \t\n";
    char **tokens = tokenizer(input, delimiters);   // Tokenizing the input command
    expand_variables(tokens);    // Expand variables in the tokens
    int i = 0;
    while (tokens[i] != NULL)
	{
        printf("%s\n", tokens[i]); // Print the tokens to check if variables were expanded
        i++;
    }
    i = 0;
    while (tokens[i] != NULL)
	{
        free(tokens[i]); // Free allocated memory
        i++;
    }
    free(tokens);
    return 0;
}
