/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:09:43 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/23 22:24:59 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

/* input_ptr: ptr to ptr to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	token_start: pointer to the pointer to the first character of the token
	token_end: pointer to the pointer to the last character of the token
	return: token type
	note: the function is called by: parse_redir(), parse_pipe(), parse_exec()
 */

int get_token(char **input_ptr, char *end_str, char **token_start, char **token_end)
{
    char	*current_pos;
    int		token_type;

    current_pos = *input_ptr;
    while (current_pos < end_str && ft_strchr(WHITESPACE, *current_pos))
		current_pos++;
	if (token_start != NULL)
		*token_start = current_pos;
	if (*current_pos == '\'')
	{
		token_type = 'q';
		current_pos++;
		*token_start = current_pos;
		while (current_pos < end_str && *current_pos != '\'')
			current_pos++;
	}
	else if (*current_pos == '\"')
	{
		token_type = 'd';
		current_pos++;
		*token_start = current_pos;
		while (current_pos < end_str && *current_pos != '\"')
            current_pos++;
	}
    else if (*current_pos == 0)
        token_type = 0;
	else if (*current_pos == '|' || *current_pos == '<' || *current_pos == '>')
	{
        token_type = *current_pos;
		if (*current_pos == '>' && *(current_pos + 1) == '>')
		{
			token_type = 'x';
			current_pos++;
		}
		if (*current_pos == '<' && *(current_pos + 1) == '<')
		{
			token_type = 'h';
			current_pos++;
		}
		current_pos++;
    }
	else
	{
        token_type = 'a';
        while (current_pos < end_str && !ft_strchr(WHITESPACE, *current_pos)
			&& !ft_strchr(SYMBOLS, *current_pos))
            current_pos++;
    }
    if (token_end != NULL)
        *token_end = current_pos;
    while (current_pos < end_str && ft_strchr(WHITESPACE, *current_pos))
        current_pos++;
    *input_ptr = current_pos;
    return (token_type);
}