/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:05:32 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/23 22:03:16 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_env_var(t_exec *cmd, int args, t_info **info, t_env **head)
{
	char	*token;

	expand_env(&cmd->argv[args], head);
	token = expand_env_in_str(cmd->argv[args], (*info)->exitstatus, head);
	free(cmd->argv[args]);
	cmd->argv[args] = ft_strdup(token);
	free(token);
}

/* 	
	Function to parse execution commands
	position_ptr: ptr to ptr to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: parse_pipe()
*/
t_cmd	*parse_exec(char **pos_ptr, char *end_str, t_info **info, t_env **head)
{
	t_cmd	*cmd;
	t_exec	*exec_command;
	int		args; 

	args = 0;
	cmd = exec_cmd();
	exec_command = (t_exec *)cmd;
	cmd = parse_redir(cmd, pos_ptr, end_str, info);
	while (!check_next_token(pos_ptr, end_str, "|"))
	{
		(*info)->token_type = get_token(pos_ptr, end_str,
				&(*info)->t_start, &(*info)->t_end);
		if ((*info)->token_type == 0)
			break ;
		exec_command->argv[args] = make_copy((*info)->t_start, (*info)->t_end);
		if ((*info)->token_type != 'q')
			expand_env_var(exec_command, args, info, head);
		args++;
		if (args >= MAXARGS)
			ft_putstr_fd("Too many arguments\n", 2);
		cmd = parse_redir(cmd, pos_ptr, end_str, info);
	}
	exec_command->argv[args] = NULL;
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
