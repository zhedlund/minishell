/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:11:11 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/25 21:32:54 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* return: pointer to the command struct
	note: the function is called by: parse_exec()
 */
t_cmd	*exec_cmd(void)
{
	t_exec	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = ' ';
	return ((t_cmd *)cmd);
}

static void	setup_redir_heredoc(t_redir *cmd, t_info **info)
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

/* sub_cmd: pointer to the command struct
	file: pointer to the file name
	type: redirection type
	return: pointer to the command struct
	note: the function is called by: parse_redir()
	note: memory allocated by malloc() must be freed by the caller
 */
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
		setup_redir_heredoc(cmd, info);
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

/* left: pointer to the left command struct
	right: pointer to the right command struct
	return: pointer to the command struct
	note: the function is called by: parse_pipe()
 */
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
