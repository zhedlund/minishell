/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipefin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 08:47:47 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/30 08:47:55 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Builtins.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <limits.h>

//annotations pending
void pipeinput(char *str, int *cfd, t_info **info)
{
	int pid;
	int	status;
	
	if ((pid = fork()) == 0)
	{
		close(cfd[0]);
		dup2(cfd[1], 1);
		ft_inputs(str, info);
		close(cfd[1]);
	}
	close(cfd[1]);
	dup2(cfd[0], 0);
	//close(cfd[0]);
	waitpid(0, &status, 0);
	//close(cfd[0]);
	//waitpid(0, &status, 0);
}

//annotations pending
void	ft_pipesmain(char **pipearray, t_info **info)
{
	int	fd[2];
	int	i;
	//should this be malloced and freed?
	char	buf[100000];
	//int	pid, status;
	int	n;
	
	n = 0;
	i = 0;
	while (pipearray[i] != NULL)
	{
		pipe(fd);
			//printf("pipecreated\n");
		pipeinput(pipearray[i], fd, info);
		if (pipearray[i + 1] != NULL)
			close(fd[0]);
			//close(fd[1]);
		i++;
	}
	if (pipearray[i] == NULL)
	{
		i = 0;
		if ((n = read(fd[0], buf, 100000)) >= 0)
		{
			buf[n] = '\0';
			while (buf[i] != '\0')
				i++;
			if ((i - 1) == '\n') 
				printf("%s\n", buf);
			else
				printf("%s", buf);
		}
	}
	close (fd[0]);
}

//annotations pending
//the process forked here covers the entire pipe command line only exiting when all the child processes are complete
//still something mysterious about this, but it seems essential to exiting properly back to the minishell rather than the terminal shell
int pipeprep(char *input, t_info **info)
{
	char	**pipearray;
	int	i;
	int	pid;
	int	status;
	
	i = 0;
	pipearray = ft_split(input, '|');
	//blue - a plaster for ls | << here - but it doesn't work with a longer command line
	//if (pipearray[2] == NULL)
	//{
	//	if (pipearray)
	//		ft_freearray(pipearray);
	//	return (1);
	//}
	while (pipearray[i] != NULL)
	{
		pipearray[i] = ft_strtrim(pipearray[i], " ");
		//printf("pip %s\n", pipearray[i]);
		i++;
	}
	if ((pid = fork()) == 0)
	{
		ft_pipesmain(pipearray, info);
		exit(0);
	}
	waitpid(0, &status, 0);
	ft_freearray(pipearray);
	return(0);
}
/*
int main(void)
{
	char a[] = "pwd | ls | pwd | grep | pwd | pwd | pwd | pwd | ls | pwd | ls | pwd | grep | pwd | pwd | pwd | pwd | ls";
	pipeprep(a);
	return(0);
}
*/
