/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:09:43 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/15 12:09:45 by jelliott         ###   ########.fr       */
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
    if (*current_pos == 0)
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
			token_type = 'h'; // heredoc token type
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

/* position_ptr: pointer to the pointer to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	token_char: pointer to the string of token characters
	return: 1 if the next token is a token character, 0 otherwise
	note: the function is called by: parse_redir(), parse_pipe(), parse_exec(), parse_cmd()
 */
int check_next_token(char **position_ptr, char *end_str, char *token_char)
{
	char *current_pos;

	current_pos = *position_ptr;
	while (current_pos < end_str && ft_strchr(WHITESPACE, *current_pos))
		current_pos++;
	*position_ptr = current_pos;
	return (*current_pos && ft_strchr(token_char, *current_pos));
}

/* 	start_ptr: pointer to the first character of the string to be copied
	end_ptr: pointer to the last character of the string to be copied
	return: pointer to the copy of the string
	note: the copy is allocated on the heap and must be freed by the caller */
char *make_copy(char *start_ptr, char *end_ptr)
{
	size_t len;
	char *copy;

	len = end_ptr - start_ptr;
	copy = malloc(len + 1);
	if (copy != NULL)
		ft_strlcpy(copy, start_ptr, len + 1); //copy n characters from s to c and ensure null-termination
	return (copy);
}
