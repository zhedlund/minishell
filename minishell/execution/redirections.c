/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:39 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/25 21:33:20 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	open_file(t_redir *redir_cmd, int *fd_redirect)
{
	if (redir_cmd->type == '>' || redir_cmd->type == 'x')
	{
		*fd_redirect = open(redir_cmd->file, redir_cmd->mode, 0666);
		if (*fd_redirect < 0)
		{
			perror(redir_cmd->file);
			exit(2);
		}
	}
	else if (redir_cmd->type == '<')
	{
		*fd_redirect = open(redir_cmd->file, redir_cmd->mode);
		if (*fd_redirect < 0)
		{
			perror(redir_cmd->file);
			exit(1);
		}
	}
	else
	{
		*fd_redirect = open("/tmp/hdtemp", redir_cmd->mode);
		if (*fd_redirect < 0)
			exit(0);
	}
}

/*  redir_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void	handle_redir_cmd(t_redir *redir_cmd, t_env **head, t_info **info)
{
	int	fd_redirect;

	open_file(redir_cmd, &fd_redirect);
	if (dup2(fd_redirect, redir_cmd->fd) < 0)
	{
		perror("dup2");
		exit(1);
	}
	run_cmd(redir_cmd->cmd, head, info);
}
