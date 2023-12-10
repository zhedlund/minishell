/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:25:54 by zhedlund          #+#    #+#             */
/*   Updated: 2023/12/10 19:27:17 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* example main for minishell
 * note: this is not a working program, just an outline
*/
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
        execute_command(tokens);
        free(input);
        free(tokens);
    }
    return (0);
}