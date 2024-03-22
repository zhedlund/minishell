/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longredirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:08:42 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/30 18:08:45 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Builtins.h"
#include <fcntl.h>
#include <sys/stat.h>
/*
void	ft_longredirunit(char **redirarray, char *command)
{
	static int	file_descriptor1;
	static int	file_descriptor2;
        int	fd[2];
        int	pid;
        int	status;
        int	redirtype;
	
	filename > filename >
	filename > filename <
	filename > filename NULL
	
	file_descriptor1 = ft_getfiledescriptor(redirarray[2], redirarray[1]);
        file_descriptor2 = ft_getfiledescriptor(redirarray[2], redirarray[3]);
        if (file_descriptor2 != -1 && ...) //this isn't the correct condition
        {
        	redirtype = ft_redirtype(redirarray[2]);
        	fd[1] = file_descriptor; //this is an if condition NULL or '<'
        	if ((pid = fork()) == 0)
        	{
        		close(fd[0]);
        		dup2(fd[1], redirtype);
        		ft_inputs(command);
        		close(fd[1]);
        		exit (0);
		}
        	wait(&status);
        }
        else
        {
        	printf("minishell: %s", redirarray[3]);
        	printf(": No such file or directory\n");
        	exit(0); //is this an issue?
	}
}
*/
////////////////////////////above is old
void	ft_longredirinitial(char **redirarray, t_info **info)
{
	char **longredir;
	int	pid;
	int	status;
	
	longredir = (char **)malloc(sizeof(char *) * 4); //this has been altered
	longredir[3] = NULL;
	longredir[0] = ft_strdup(redirarray[0], 0);
	longredir[1] = ft_strdup(redirarray[1], 0);
	longredir[2] = ft_strdup(redirarray[2], 0);
	ft_simpleredir(longredir, info);
	ft_freearray(longredir);
}
/*
////function that executes the command depending if < file exists
void ft_inend(char **unit, int prevfd)
{
	int	file_descriptor;
	int	fd[2];
        int	pid;
        int	status;
        int	redirtype;
        
	file_descriptor = ft_getfiledescriptor(unit[2], unit[1]);
	if (file_descriptor != -1)
	{
        	redirtype = ft_redirtype(unit[2]);
        	fd[1] = prevfd;
        	if ((pid = fork()) == 0)
        	{
        		close(fd[0]);
        		dup2(fd[1], redirtype);
        		ft_inputs(command);
        		close(fd[1]);
        		exit (0);
		}
        	wait(&status);
        }
        else
        {
        	printf("minishell: %s", unit[1]);
        	printf(": No such file or directory\n");
        	exit(0); //is this an issue?
	}	
}
*/
void ft_inend(char **unit, char	*file, char *redir, t_info **info)
{
	int	fd[2];
        int	pid;
        int	status;
        int	redirtype;
        int	file_descriptor;
        
        file_descriptor = ft_getfiledescriptor(redir, file);
        redirtype = ft_redirtype(redir);
        fd[1] = file_descriptor;
        if ((pid = fork()) == 0)
        {
        	close(fd[0]);
        	dup2(fd[1], redirtype);
        	ft_inputs(unit[0], info);
        	close(fd[1]);
        	exit (0);
	}
        wait(&status);
}

void ft_outend(char **unit, t_info **info)
{
	int	fd[2];
        int	pid;
        int	status;
        int	redirtype;
        int	file_descriptor;
        
        file_descriptor = ft_getfiledescriptor(unit[2], unit[3]);
        redirtype = ft_redirtype(unit[2]);
        pipe(fd);
        fd[1] = file_descriptor;
        if ((pid = fork()) == 0)
        {
        	close(fd[0]);
        	dup2(fd[1], redirtype);
        	ft_inputs(unit[0], info);
        	close(fd[1]);
        	//exit (0);
	}
        wait(&status);
}

//decide what subfunction to send to
////function that executes the command depending if < file exists
////function that executes the command if we have reached the end
void	ft_whatcombination(char **unit, t_info **info)
{
	int	file_descriptor;
	//int	file_descriptor2;
	static char	*prevfilename;
	static char	*prevredir;
	
	//if (!prevfilename)
	//	prevfilename = NULL;
	//if (!prevredir)
	//	prevredir = NULL;	
	if (unit[2][0] == '<')
	{
		file_descriptor = ft_getfiledescriptor(unit[2], unit[3]);
		if (file_descriptor != -1)
			ft_inend(unit, prevfilename, prevredir, info);
		else
        	{
        		printf("minishell: %s", unit[3]);
        		printf(": No such file or directory\n");
        		//exit(0); //is this an issue? e.g. freeing
		}	
	}
	else
	{
		prevfilename = unit[3];
		prevredir = unit[2];
		file_descriptor = ft_getfiledescriptor(unit[2], unit[3]);
		if (unit[4] == NULL)
			ft_outend(unit, info);
	}
	//free(prevfilename);
	//free(prevredir);
}

//use an int place to save lines
//setting to NULL is also important - another way to reach the end of the command line
//we make a smaller array which consists in a commandline unit i.e. command, filename, redir, filename, redir
//this can be used to know whether or not we need to execute the command after creating/truncating files
//the array can take three forms:
//filename > filename >
//filename > filename <
//filename > filename NULL
//filename < filename NULL
//filename < filename redirsign
//we then go to a new function to decide what form we have and where to pass it
void	ft_longredir(char **redirarray, char *command, t_info **info)
{
	char	**longredir;
	int	first;
	int	redir;
	int	second;
	int	pid;
	int	status;
	static char	*command2;
	int	redir2;
	
	first = 2;
	second = 4;
	redir = 3;
	redir2 = 5;
	if (!command2)
		command2 = ft_strdup(command, 0);
	ft_longredirinitial(redirarray, info); //this is an issue if only two redir commands
	if ((pid = fork()) == 0)
	{
		longredir = (char **)malloc(sizeof(char *) * 6);
		longredir[5] = NULL;
		longredir[0] = command2;
		while(redirarray[redir] != NULL)
		{
			longredir[1] = redirarray[first];
			longredir[2] = redirarray[redir];
			longredir[3] = redirarray[second];
			if (redirarray[second + 1] != NULL)
				longredir[4] = redirarray[redir2];
			else
				longredir[4] = NULL;
			ft_whatcombination(longredir, info);
			if (longredir[2][0] == '<')
				break ;
			first += 2;
			second += 2;
			redir += 2;
			redir2 += 2;
		}
		//ft_freearray(longredir);
		exit(0);
	}
	wait(&status);
	free(command2);
}
