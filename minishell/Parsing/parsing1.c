/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:05:32 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/21 14:23:11 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

/* ps: pointer to the pointer to the first character of the string to be parsed
	es: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is recursive
	note: the function is called by: parse_line(), parse_cmd(), run_cmd(), main(), get_cmd()
 */
t_cmd	*parse_pipe(char **position_ptr, char *end_str, t_info **info, t_env **head)
{
	t_cmd *cmd;

	cmd = parse_exec(position_ptr, end_str, info, head);
	if (check_next_token(position_ptr, end_str, "|"))
	{
		get_token(position_ptr, end_str, 0, 0);
		cmd = pipe_cmd(cmd, parse_pipe(position_ptr, end_str, info, head));
	}
	return (cmd);
}

/* position_ptr: pointer to the pointer to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: parse_cmd()
 */
t_cmd	*parse_line(char **position_ptr, char *end_str, t_info **info, t_env **head)
{
	t_cmd *cmd;

	cmd = parse_pipe(position_ptr, end_str, info, head);
	return (cmd);
}

/* str: pointer to the first character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: main()
 */
t_cmd	*parse_cmd(char *str, t_info **info, t_env **head)
{
	char *end_str;
	t_cmd *cmd;

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
