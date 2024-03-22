/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:11:11 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/23 17:46:29 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

t_cmd	*exec_cmd(void)
{
	t_exec	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = ' ';
	return ((t_cmd *)cmd);
}

void	ft_heredocredirect(t_redir *cmd, t_info **info)
{
	if ((*info)->first == true)
	{
		cmd->mode = O_RDONLY;
		(*info)->first = false;
	}
	else
		cmd->mode = O_TRUNC;
	cmd->fd = 0;
}

t_cmd	*redir_cmd(t_cmd *sub_cmd, char *file, int type, t_info **info)
{
	t_redir	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = type;
	cmd->cmd = sub_cmd;
	cmd->file = file;
	if (type == '<')
	{
		cmd->mode = O_RDONLY;
		cmd->fd = 0;
	}
	else if (type == 'h')
		ft_heredocredirect(cmd, info);
	else if (type == 'x')
	{
		cmd->mode = O_WRONLY | O_CREAT | O_APPEND;
		cmd->fd = 1;
	}
	else
	{
		cmd->mode = O_WRONLY | O_CREAT | O_TRUNC;
		cmd->fd = 1;
	}
	return ((t_cmd *)cmd);
}

t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = '|';
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
