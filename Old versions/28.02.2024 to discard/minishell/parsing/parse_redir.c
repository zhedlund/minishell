/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:24:48 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/28 15:24:52 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

/* 
	cmd: pointer to the cmd struct
	position_ptr: ptr to ptr to the first character of the string to be parsed
	end_str: ptr to the last character of the string to be parsed
	return: ptr to the cmd struct
	note: the function is called by: parse_exec(), parse_pipe()
 */
t_cmd	*parse_redir(t_cmd *cmd, char **position_ptr, char *end_str,
						t_info **info)
{
	int		redir_type;
	char	*file_start;
	char	*file_end;

	while (check_next_token(position_ptr, end_str, "<>"))
	{
		redir_type = get_token(position_ptr, end_str, 0, 0);
		if (get_token(position_ptr, end_str, &file_start, &file_end) != 'a')
		{
			ft_putstr_fd("missing file for redirection\n", 2);
			exit(-1);
		}
		if (redir_type == '<')
			cmd = redir_cmd(cmd, make_copy(file_start, file_end), '<', info);
		else if (redir_type == '>')
			cmd = redir_cmd(cmd, make_copy(file_start, file_end), '>', info);
		else if (redir_type == 'x')
			cmd = redir_cmd(cmd, make_copy(file_start, file_end), 'x', info);
		else if (redir_type == 'h')
			cmd = redir_cmd(cmd, make_copy(file_start, file_end), 'h', info);
	}
	return (cmd);
}
