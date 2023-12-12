/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:42:47 by zhedlund          #+#    #+#             */
/*   Updated: 2023/12/10 19:44:19 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_TOKENS 64
#define MAX_TOKEN_LEN 128

/* Function to tokenize input
 * @param input: input string
 * @param delimiters: delimiters
 * @return: array of tokens
 */
char **tokenizer(char *input, const char *delimiters)
{
    char **tokens;
	char *current_token;
	int i;

	current_token = ft_strtok(input, delimiters);
	tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (!tokens)
		return (NULL);
	i = 0;
    while (current_token != NULL)
	{
        tokens[i] = malloc(MAX_TOKEN_LEN * sizeof(char));
        if (!tokens[i])
			return (NULL);
        ft_strcpy(tokens[i], current_token);
        i++;
        if (i >= MAX_TOKENS)
		{
            printf("Maximum number of tokens reached.\n");
            break;
        }
        current_token = ft_strtok(NULL, delimiters);
    }
    tokens[i] = NULL;
    return (tokens);
}

/*
int main() {
    char input[] = "ls -l -a";
    const char delimiters[] = " \t\n"; // Delimiters: space, tab, newline
    char **tokens = tokenizer(input, delimiters);

    // Print tokens for testing
    int i = 0;
    while (tokens[i] != NULL) {
        printf("Token %d: %s\n", i, tokens[i]);
        i++;
    }

    // Free memory allocated for tokens
    for (int j = 0; j < MAX_TOKENS; j++) {
        free(tokens[j]);
    }
    free(tokens);

    return 0;
} */