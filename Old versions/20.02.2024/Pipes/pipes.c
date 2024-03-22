/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:00 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/15 12:18:02 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

/* cmd: pointer to the command struct
	fd_pipe: file descriptor array
	return: void
	note: the function is called by: handle_pipe_cmd()
 */
void handle_child_process(t_cmd *cmd, int fd_pipe[])
{
    close(fd_pipe[1]);
    dup2(fd_pipe[0], STDIN_FILENO);
    run_cmd(((t_pipe *)cmd)->right);
    close(fd_pipe[0]);
}

/* cmd: pointer to the command struct
	fd_pipe: file descriptor array
	pid: process id
	return: void
	note: the function is called by: handle_pipe_cmd()
 */
void handle_parent_process(t_cmd *cmd, int fd_pipe[], int pid)
{
    close(fd_pipe[0]);
    dup2(fd_pipe[1], STDOUT_FILENO);
    run_cmd(((t_pipe *)cmd)->left);
    close(fd_pipe[1]);
    wait(&pid);
}

/* pipe_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void handle_pipe_cmd(t_pipe *pipe_cmd)
{
    int fd_pipe[2];
    int pid;

    if (pipe(fd_pipe) < 0)
	{
        perror("pipe");
        exit(0);
    }
    pid = fork();
    if (pid < 0)
	{
        perror("fork");
        exit(1);
    }
    if (pid == 0)
        handle_child_process((t_cmd *)pipe_cmd, fd_pipe);
    else
        handle_parent_process((t_cmd *)pipe_cmd, fd_pipe, pid);
}
