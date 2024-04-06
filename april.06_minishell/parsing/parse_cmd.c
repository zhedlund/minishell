/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:05:32 by jelliott          #+#    #+#             */
/*   Updated: 2024/03/22 15:11:43 by zhedlund         ###   ########.fr       */
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

/* 	
	Function to parse execution commands
	position_ptr: ptr to ptr to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: parse_pipe()
*/
t_cmd	*parse_exec(char **position_ptr, char *end_str, t_info **info,
					t_env **head)
{
	t_cmd	*cmd;
	t_exec	*exec_command;

	cmd = exec_cmd();
	exec_command = (t_exec *)cmd;
	cmd = parse_redir(cmd, position_ptr, end_str, info);
	(*info)->args = 0;
	while (!check_next_token(position_ptr, end_str, "|"))
	{
		(*info)->token_type = get_token(position_ptr, end_str,
				&(*info)->token_start, &(*info)->token_end);
		if ((*info)->token_type == 0)
			break ;
		copy_tokens_and_expand(exec_command, info, head);
		(*info)->args++;
		if ((*info)->args >= MAXARGS)
			ft_putstr_fd("Too many arguments\n", 2);
		cmd = parse_redir(cmd, position_ptr, end_str, info);
	}
	exec_command->argv[(*info)->args] = NULL;
	return (cmd);
}

/*
	position_ptr: ptr to ptr to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is recursive
	note: the function is called by: parse_line(), pipe_cmd(), parse_pipe()
 */
t_cmd	*parse_pipe(char **position_ptr, char *end_str, t_info **info,
					t_env **head)
{
	t_cmd	*cmd;

	cmd = parse_exec(position_ptr, end_str, info, head);
	if (check_next_token(position_ptr, end_str, "|"))
	{
		get_token(position_ptr, end_str, 0, 0);
		cmd = pipe_cmd(cmd, parse_pipe(position_ptr, end_str, info, head));
	}
	return (cmd);
}

/* 
	position_ptr: ptr to ptr to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: parse_cmd()
 */
t_cmd	*parse_line(char **position_ptr, char *end_str, t_info **info,
					t_env **head)
{
	t_cmd	*cmd;

	cmd = parse_pipe(position_ptr, end_str, info, head);
	return (cmd);
}

/* str: pointer to the first character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: main()
 */
t_cmd	*parse_cmd(char *str, t_info **info, t_env **head)
{
	char	*end_str;
	t_cmd	*cmd;

	end_str = str + ft_strlen(str);
	cmd = parse_line(&str, end_str, info, head);
	check_next_token(&str, end_str, "");
	if (str != end_str)
	{
		ft_putstr_fd("leftovers in str\n", 2);
		exit(1);
	}
	return (cmd);
}
