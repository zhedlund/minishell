/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipemain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:29:40 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/19 17:29:42 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Builtins.h"

//how to make sure that the commands execute in the child process
//and are saved as input/output?
//in a line with a pipe, we probably want to split where there is a pipe??
//if the next array entry is NULL, then that's the final one - instead of has pipe...although why would has pipe not work?
/*int	ft_child(char *pipestring, bool final)
{
	int	fd[2];
	int	pid;
	int	status;
	
	if (pipe(fd) == -1)
	 {
            printf("PIPE ERROR\n");
            //will need to free and then exit
           exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		printf("PID ERROR\n");
		exit(1);
	}
	if (!pid)
	{
		printf("in | process\n");
		if ((dup2(fd[1], STDIN_FILENO) == -1) || close(fd[0]) == -1 || close(fd[1]) == -1)
            		printf("Error with pipes\n");
            		//return err("error: fatal\n");
            	ft_inputs(pipestring);
		//what do we execute?
	}
	waitpid(pid, &status, 0);
	if ((dup2(fd[0], 0) == -1) || close(fd[0]) == -1 || close(fd[1]) == -1)
            		printf("Error with pipes2\n");
	//if (final && (dup2(fd[0], 0) == -1) || close(fd[0]) == -1 || close(fd[1]) == -1)
         //   	printf("Error with pipes2\n");
            		//return err("error: fatal\n");
	return WIFEXITED(status) && WEXITSTATUS(status);
}*/
/*
void	ft_child(char *pipearray, t_info **info) 
{
	int	fd_pipe[2];
	int	p_id;
	
	//ft_inputs(pipearray);
	if (pipe(fd_pipe) < 0)
	{
        	printf("error: fatal\n");
        	exit (1);
	}
    	if ((p_id = fork()) < 0)
	{
		fprintf(stderr, "fork has failed\n");
		exit(0);
	}
	//else if (p_id == 0)
	//{
	//	close(fd_pipe[0]);
	//	dup2(fd_pipe[1], STDIN_FILENO);
		//ft_child(pipearray);
	//	close(fd_pipe[1]);
	//}
	//else
	//{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDOUT_FILENO);
		//ft_child(pipearray);
		ft_inputs(pipearray, info);
		close(fd_pipe[0]);
		wait(&p_id);
	//}
	return ;
}
*/
int	ft_pipesmain(char *arraystring, t_info **info)
{
	int	i;
	char	**pipearray;
	int	pid;
	int	fd[2];
	int	status;
	
	i = 0;
	pipearray = ft_split(arraystring, '|');
	while (pipearray[i] != NULL)
	{
		pipearray[i] = ft_strtrim(pipearray[i], " ");
		i++;
	}
	i = 0;
	pipe(fd);
	//close(fd[0]);
	pid = fork();
	{
		close(fd[0]);
		dup2(fd[1], STDIN_FILENO);
		ft_inputs(pipearray[i], info);
		close(fd[1]);
		//ft_inputs(pipearray[i]);
		//ft_child(pipearray[i + 1]);
		exit(0);
	}
	wait(&status);
	//	ft_child(pipearray, i);
	//wait(&r);
	//free things
	ft_freearray(pipearray); //is this needed?
	return (0);
}
