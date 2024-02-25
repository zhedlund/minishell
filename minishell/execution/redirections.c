/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:39 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/11 19:39:48 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

/* redir_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void handle_redir_cmd(t_redir *redir_cmd, t_env **head, t_info **info)
{
    int fd_redirect;

    if (redir_cmd->type == '>')
	{
        if ((fd_redirect = open(redir_cmd->file, redir_cmd->mode, 0666)) < 0) // 0666 - read and write permissions for user, group, and others. no execution permissions
		{
			perror("open");
            exit(2);
        }
    }
	else if (redir_cmd->type == 'x')
	{
		if ((fd_redirect = open(redir_cmd->file, redir_cmd->mode, 0666)) < 0)
		{
			perror("open");
			exit(2);
		}
	}
	else if (redir_cmd->type == '<')
	{
        if ((fd_redirect = open(redir_cmd->file, redir_cmd->mode)) < 0)
		{
			perror("open");
            exit(2);
        }
        }
	else
	{
         if ((fd_redirect = open("/tmp/hdtemp", redir_cmd->mode)) < 0)
        	exit(0);
    }
    if (dup2(fd_redirect, redir_cmd->fd) < 0)
	{
        perror("dup2");
        exit(1);
    }
    run_cmd(redir_cmd->cmd, head, info);
}
