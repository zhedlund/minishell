/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:09:43 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/25 21:34:25 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_whitespace(char **current_pos, char *end_str)
{
	while (*current_pos < end_str && ft_strchr(WHITESPACE, **current_pos))
		(*current_pos)++;
}

static void	skip_whitespace_and_symbols(char **current_pos, char *end_str)
{
	while (*current_pos < end_str && !ft_strchr(WHITESPACE, **current_pos)
		&& !ft_strchr(SYMBOLS, **current_pos))
		(*current_pos)++;
}

static void	handle_quotes(char **current_pos, char *end_str,
							char **token_start, int token_type)
{
	(*current_pos)++;
	*token_start = *current_pos;
	if (token_type == '\'')
	{
		while (*current_pos < end_str && **current_pos != '\'')
			(*current_pos)++;
		if (**current_pos == '\'')
			(*current_pos)++;
	}
	else if (token_type == '\"')
	{
		while (*current_pos < end_str && **current_pos != '\"')
			(*current_pos)++;
		if (**current_pos == '\"')
			(*current_pos)++;
	}
}

static void	handle_other_tokens(char **current_pos, int *token_type)
{
	*token_type = **current_pos;
	if (**current_pos == '>' && *(*current_pos + 1) == '>')
	{
		*token_type = 'x';
		(*current_pos)++;
	}
	if (**current_pos == '<' && *(*current_pos + 1) == '<')
	{
		*token_type = 'h';
		(*current_pos)++;
	}
	(*current_pos)++;
}

/* input_ptr: ptr to ptr to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	token_start: pointer to the pointer to the first character of the token
	token_end: pointer to the pointer to the last character of the token
	return: token type
	note: the function is called by: parse_redir(), parse_pipe(), parse_exec()
 */

int	get_token(char **input_ptr, char *end_str, char **token_start, 
				char **token_end)
{
	char	*current_pos;
	int		token_type;

	token_type = 'a';
	current_pos = *input_ptr;
	skip_whitespace(&current_pos, end_str);
	if (token_start != NULL)
		*token_start = current_pos;
	if (*current_pos == '\'' || *current_pos == '\"')
	{
		token_type = *current_pos;
		handle_quotes(&current_pos, end_str, token_start, token_type);
	}
	else if (*current_pos == 0)
		token_type = 0;
	else if (*current_pos == '|' || *current_pos == '<' || *current_pos == '>')
		handle_other_tokens(&current_pos, &token_type);
	else
		skip_whitespace_and_symbols(&current_pos, end_str);
	if (token_end != NULL)
		*token_end = current_pos;
	skip_whitespace(&current_pos, end_str);
	*input_ptr = current_pos;
	return (token_type);
}
