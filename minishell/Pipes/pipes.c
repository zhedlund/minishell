/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:00 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/14 13:48:08 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

/* cmd: pointer to the command struct
	fd_pipe: file descriptor array
	return: void
	note: the function is called by: handle_pipe_cmd()
 */
void handle_child_process(t_cmd *cmd, int fd_pipe[], int pid, t_env **head, t_info **info)
{
    close(fd_pipe[1]);
    dup2(fd_pipe[0], STDIN_FILENO);
    run_cmd(((t_pipe *)cmd)->right, head, info);
    close(fd_pipe[0]);
    wait(&pid);
}

/* cmd: pointer to the command struct
	fd_pipe: file descriptor array
	pid: process id
	return: void
	note: the function is called by: handle_pipe_cmd()
 */
void handle_parent_process(t_cmd *cmd, int fd_pipe[], int pid, int status, t_env **head, t_info **info)
{
    close(fd_pipe[0]);
    dup2(fd_pipe[1], STDOUT_FILENO);
    run_cmd(((t_pipe *)cmd)->left, head, info);
    close(fd_pipe[1]);
    wait(&pid);
	//if (WIFEXITED(pid))
		//printf("Exit status handle_parent_process: %d\n", WEXITSTATUS(status));
}

/* pipe_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void handle_pipe_cmd(t_pipe *pipe_cmd, t_env **head, t_info **info)
{
    int fd_pipe[2];
    int pid;
	int	status;
    if (pipe(fd_pipe) < 0)
	{
        perror("pipe");
        exit(1);
    }
    pid = fork();
    if (pid < 0)
	{
        perror("fork");
        exit(1);
    }
    //printf("pipe command right%s\n", (pipe_cmd)->right);
    //printf("pipe command left%s\n", (pipe_cmd)->left);
	if (pid == 0)
        	handle_child_process((t_cmd *)pipe_cmd, fd_pipe, pid, head, info);
	else
        	handle_parent_process((t_cmd *)pipe_cmd, fd_pipe, pid, status, head, info);
}
