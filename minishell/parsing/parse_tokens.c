/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:08:48 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/25 21:34:42 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 	position_ptr: ptr to ptr to first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	token_char: pointer to the string of token characters
	return: 1 if the next token is a token character, 0 otherwise
	note: the function is called by: parse_redir(), parse_pipe(),
	parse_exec(), parse_cmd()
 */
int	check_next_token(char **position_ptr, char *end_str, char *token_char)
{
	char	*current_pos;

	current_pos = *position_ptr;
	while (current_pos < end_str && ft_strchr(WHITESPACE, *current_pos))
		current_pos++;
	*position_ptr = current_pos;
	return (*current_pos && ft_strchr(token_char, *current_pos));
}

static void	expand_env_var(t_exec *cmd, int args, t_info **info, t_env **head)
{
	char	*token;

	expand_env(&cmd->argv[args], head);
	token = expand_env_in_str(cmd->argv[args], (*info)->exitstatus, head);
	free(cmd->argv[args]);
	cmd->argv[args] = token;
}

/* Function to handle token parsing and filling arguments
	exec_cmd: pointer to the cmd struct
	cmd: pointer to the pointer to the command struct
	position_ptr: ptr to ptr to first character of the string to be parsed
	end_str: ptr to the last character of the string to be parsed
	note: the function is called by: parse_exec()
*/

void	parse_tokens(t_exec *exec_cmd, t_cmd **cmd, char **position_ptr,
						char *end_str, t_info **info, t_env **head)
{
	int		args;
	char	*token_start;
	char	*token_end;
	int		token_type;

	args = 0;
	while (!check_next_token(position_ptr, end_str, "|"))
	{
		token_type = get_token(position_ptr, end_str,
				&token_start, &token_end);
		if (token_type == 0)
			break ;
		if (token_type == '\'' || token_type == '\"')
			exec_cmd->argv[args] = make_copy(token_start, token_end -1);
		else
			exec_cmd->argv[args] = make_copy(token_start, token_end);
		if (token_type != '\'')
			expand_env_var(exec_cmd, args, info, head);
		args++;
		if (args >= MAXARGS)
			ft_putstr_fd("Too many arguments\n", 2);
		*cmd = parse_redir(*cmd, position_ptr, end_str, info);
	}
	exec_cmd->argv[args] = NULL;
}
