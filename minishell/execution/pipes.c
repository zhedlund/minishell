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
void handle_child_process(t_cmd *cmd, int fd_pipe[], t_env **head, t_info **info)
{
    close(fd_pipe[1]);
    dup2(fd_pipe[0], STDIN_FILENO);
    run_cmd(((t_pipe *)cmd)->right, head, info);
    close(fd_pipe[0]);
    //exit((*info)->exitstatus);
}

/* cmd: pointer to the command struct
	fd_pipe: file descriptor array
	pid: process id
	return: void
	note: the function is called by: handle_pipe_cmd()
 */
void handle_parent_process(t_cmd *cmd, int fd_pipe[], t_env **head, t_info **info)
{
    close(fd_pipe[0]);
    dup2(fd_pipe[1], STDOUT_FILENO);
    run_cmd(((t_pipe *)cmd)->left, head, info);
    close(fd_pipe[1]);
    wait(&(*info)->infopid);
}

/* pipe_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void handle_pipe_cmd(t_pipe *pipe_cmd, t_env **head, t_info **info)
{
    int fd_pipe[2];
    int pid;
	//int	status;

    //(*info)->infostatus = status;
    if (pipe(fd_pipe) < 0)
	{
        perror("pipe");
        exit(0);
    }
    pid = fork();
     (*info)->infopid = pid;
    if (pid < 0)
	{
        perror("fork");
        exit(1);
    }
    if ((*info)->solocat == false)
	{
        if (pid == 0)
            	handle_parent_process((t_cmd *)pipe_cmd, fd_pipe, head, info);
	    else
        	    handle_child_process((t_cmd *)pipe_cmd, fd_pipe, head, info);
    }
    if ((*info)->solocat == true)
    {
        if (pid == 0)
            	handle_child_process((t_cmd *)pipe_cmd, fd_pipe, head, info);
	    else
        	    handle_parent_process((t_cmd *)pipe_cmd, fd_pipe, head, info);
    }
}

/* return: pid of the child process
 * note: the function is called by: run_cmd()
 * Fork but perror on failure
 */
  
int fork_process(void)
{
	int pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}
