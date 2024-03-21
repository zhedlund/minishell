/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubleredirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 19:32:57 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/31 19:32:59 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Builtins.h"
#include <fcntl.h>
#include <sys/stat.h>

void	ft_doubleexecute(char **redirarray, t_info **info)
{
	int	fd[2];
        int	pid;
        int	status;
        int	redirtype;
        int	file_descriptor;
        
        file_descriptor = ft_getfiledescriptor(redirarray[1], redirarray[2]);
	file_descriptor = ft_getfiledescriptor(redirarray[3], redirarray[4]);
        redirtype = ft_redirtype(redirarray[3]);
        pipe(fd);
        fd[1] = file_descriptor;
        if ((pid = fork()) == 0)
        {
        	close(fd[0]);
        	dup2(fd[1], redirtype);
        	ft_inputs(redirarray[0], info);
        	close(fd[1]);
        	exit (0);
	}
        wait(&status);
}

void	ft_doubleredirection(char **redirarray, t_info **info)
{
	int	file_descriptor;

	if (redirarray[1][0] == '<')
		ft_longredirinitial(redirarray, info);
	else if (redirarray[3][0] == '<')
	{
		file_descriptor = ft_getfiledescriptor(redirarray[1], redirarray[2]);
		file_descriptor = ft_getfiledescriptor(redirarray[3], redirarray[4]);
		if (file_descriptor != -1)
			ft_inend(redirarray, redirarray[2], redirarray[1], info);
		else
        	{
        		printf("minishell: %s", redirarray[4]);
        		printf(": No such file or directory\n");
        		//exit(0); //is this an issue? e.g. freeing
		}	
	}
	else
		ft_doubleexecute(redirarray, info);
}
