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
void handle_child_process(t_cmd *cmd, int fd_pipe[], int pid, t_env **head)
{
    close(fd_pipe[1]);
    dup2(fd_pipe[0], STDIN_FILENO);
    run_cmd(((t_pipe *)cmd)->right, head);
    close(fd_pipe[0]);
}

/* cmd: pointer to the command struct
	fd_pipe: file descriptor array
	pid: process id
	return: void
	note: the function is called by: handle_pipe_cmd()
 */
void handle_parent_process(t_cmd *cmd, int fd_pipe[], int pid, int status, t_env **head)
{
    close(fd_pipe[0]);
    dup2(fd_pipe[1], STDOUT_FILENO);
    run_cmd(((t_pipe *)cmd)->left, head);
    close(fd_pipe[1]);
    wait(&pid);
}

/* pipe_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void handle_pipe_cmd(t_pipe *pipe_cmd, t_env **head)
{
    int fd_pipe[2];
    int pid;
	int	status;
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
    //printf("pipe command right%s\n", (pipe_cmd)->right);
     //printf("pipe command left%s\n", (pipe_cmd)->left);
	if (pid == 0)
        	handle_child_process((t_cmd *)pipe_cmd, fd_pipe, pid, head);
	else
        	handle_parent_process((t_cmd *)pipe_cmd, fd_pipe, pid, status, head);
}
