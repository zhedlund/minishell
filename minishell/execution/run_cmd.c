/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:14 by jelliott          #+#    #+#             */
/*   Updated: 2024/03/26 18:06:41 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* exec_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void	handle_exec_cmd(t_exec *exec_cmd, t_env **head, t_info **info)
{
	if (exec_cmd->argv[0] == NULL 
		|| exec_cmd->argv[0][0] == '\0')
	{
		ft_multifree(head, info, exec_cmd);
		exit(0);
	}
	if ((*info)->exiting == true)
		ft_exiting(exec_cmd, head, info);
	else 
		ft_builtins_not_env(exec_cmd, head, info);
}

/*	cmd: pointer to the command struct
	return: void
	note: the function is called by: main()
 */
void	run_cmd(t_cmd *cmd, t_env **head, t_info **info)
{
	if (cmd == 0)
		exit(0);
	if (cmd->type == ' ')
		handle_exec_cmd((t_exec *)cmd, head, info);
	else if (cmd->type == '>' || cmd->type == '<' || cmd->type == 'x'
		|| cmd->type == 'h')
		handle_redir_cmd((t_redir *)cmd, head, info);
	else if (cmd->type == '|')
	{
		(*info)->inchild = true;
		handle_pipe_cmd((t_pipe *)cmd, head, info);
	}
	else
	{
		ft_putstr_fd("unknown run_cmd\n", 2);
		exit(-1);
	}
}
