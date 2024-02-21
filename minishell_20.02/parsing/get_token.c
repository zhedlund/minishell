/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:09:43 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/21 14:43:54 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

/* Parsing */ 

/* input_ptr: pointer to the pointer to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	token_start: pointer to the pointer to the first character of the token
	token_end: pointer to the pointer to the last character of the token
	return: token type
	note: the function is called by: parse_redir(), parse_pipe(), parse_exec()
 */
// function too long, needs to be split
int get_token(char **input_ptr, char *end_str, char **token_start, char **token_end)
{
    char *current_pos;
    int token_type;

    current_pos = *input_ptr;
    while (current_pos < end_str && ft_strchr(WHITESPACE, *current_pos))
        current_pos++;
    if (token_start != NULL)
        *token_start = current_pos;
	else if (*current_pos == '\'') // Check for single-quoted string
	{
		token_type = 'q'; // Single-quoted string
		current_pos++;
		*token_start = current_pos;
		while (current_pos < end_str && *current_pos != '\'')
			current_pos++;
		*token_end = current_pos;
		if (*current_pos == '\'')
		current_pos++;
	}
	else if (*current_pos == '\"') // Check for double-quoted string
	{
		token_type = 'd'; // Double-quoted string
		current_pos++;
		*token_start = current_pos;
		while (current_pos < end_str && *current_pos != '\"')
            current_pos++;
		*token_end = current_pos;
		if (*current_pos == '\"')
			current_pos++;
	}
    else if (*current_pos == 0)
        token_type = 0; // Null terminator
	else if (*current_pos == '|' || *current_pos == '<' || *current_pos == '>')
	{
        token_type = *current_pos;
		if (*current_pos == '>' && *(current_pos + 1) == '>') // append
		{
			token_type = 'x'; // append token type
			current_pos++;
		}
		if (*current_pos == '<' && *(current_pos + 1) == '<') // append
		{
			token_type = 'h'; // append token type
			current_pos++;
		}
		current_pos++;
    }
	else
	{
        token_type = 'a'; // Default token type
        while (current_pos < end_str && !ft_strchr(WHITESPACE, *current_pos) && !ft_strchr(SYMBOLS, *current_pos))
            current_pos++;
    }
    if (token_end != NULL)
        *token_end = current_pos;
    while (current_pos < end_str && ft_strchr(WHITESPACE, *current_pos))
        current_pos++;
    *input_ptr = current_pos;
    return (token_type);
}


