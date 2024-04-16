/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:00 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/25 21:33:14 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* return: pid of the child process
 * note: the function is called by: run_cmd(), handle_pipe_cmd()
 * Fork but perror on failure
 */
int	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

void	ft_free_some(t_cmd *cmd)
{
	t_exec	*tofree;

	tofree = (t_exec *)cmd;
	ft_multifree(NULL, NULL, tofree);
}

/* cmd: pointer to the command struct
	fd_pipe: file descriptor array
	return: void
	note: the function is called by: handle_pipe_cmd()
 */
static void	pipe_cmd_right(t_cmd *cmd, int fd_pipe[], t_env **head,
							t_info **info)
{
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	run_cmd(((t_pipe *)cmd)->right, head, info);
	close(fd_pipe[0]);
}

/* cmd: pointer to the command struct
	fd_pipe: file descriptor array
	return: void
	note: the function is called by: handle_pipe_cmd()
 */
static void	pipe_cmd_left(t_cmd *cmd, int fd_pipe[], t_env **head,
							t_info **info)
{
	close(fd_pipe[0]);
	dup2(fd_pipe[1], STDOUT_FILENO);
	run_cmd(((t_pipe *)cmd)->left, head, info);
	close(fd_pipe[1]);
}

/* pipe_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void	handle_pipe_cmd(t_pipe *pipe_cmd, t_env **head, t_info **info)
{
	int		fd_pipe[2];
	pid_t	pid;

	if (pipe(fd_pipe) < 0)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork_process();
	if ((*info)->solocat == false && (*info)->firstcommandmix == false)
	{
		if (pid == 0)
			pipe_cmd_left((t_cmd *)pipe_cmd, fd_pipe, head, info);
		else
			pipe_cmd_right((t_cmd *)pipe_cmd, fd_pipe, head, info);
	}
	if ((*info)->solocat == true || (*info)->firstcommandmix == true)
	{
		if (pid == 0)
			pipe_cmd_right((t_cmd *)pipe_cmd, fd_pipe, head, info);
		else
			pipe_cmd_left((t_cmd *)pipe_cmd, fd_pipe, head, info);
		free (pipe_cmd);
	}
}
