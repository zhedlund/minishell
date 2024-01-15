/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simples.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:35:37 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 19:35:56 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Builtins.h"
#include <sys/ioctl.h>

//this function is for other simple commands that are triggered using execve
//potential adjustment is if we need a /usr/bin address - e.g for gcc or vim
//perhaps can create a stack to compate these to?
int	ft_othersimples(char *input, t_info **info)
{
	char	**execarray;
	//need to make a copy of env variables and pass
	char *const env[] = { NULL }; 
	int	i;
	int	pid;
	int	status;

	i = 0;
	execarray = ft_split(input, ' ');
	while (execarray[i] != NULL)
	{
		execarray[i] = ft_strtrim(execarray[i], " ");
		i++;
	}
	execarray[0] = ft_strjoin("/usr/bin/", execarray[0], 3);
	//printf("execarray[0] == %s\n", execarray[0]);
	//printf("execarray[1] == %s\n", execarray[1]);
	//pid = fork();
	//if (pid < 0)
	//	printf("PID ERROR\n"); //will need to do more
	//else if (pid == 0)
	//{
		execve(execarray[0], execarray, env);
	//	exit(0);
	//}
	//waitpid(pid, &status, 0); //waitpid seems to be essential to recreating cat | cat | ls
	ft_freearray(execarray);
	return (0); //this is just to experiment - something more complex is required
	//check for failiure?
}

//issue that if the command isn't valid, then need to exit the redirection function
//another issue - if the command isn't valid, then this should be printed at the end
//rather than piped? presumably - save in a list and printout at the end;
//related problem if someone only enters a redirection command - with heredoc, we seem to have this sussed
//still have issues - e.g. with echoh because of the way sorted echo hello
//it might make more sense to return the individual functions and their exit statuses
void ft_siminput(char *input, t_info **info)
{
	int	i;
	
	i = 0;
	//perhaps don't need this as everything else taking care
	if (ft_strlen(input) < 2)
	{
		printf("%s", input);
		printf(": command not found\n");
		//return ;
	}
	else if ((ft_strlen(input) == 4 && ft_strncmp(input, "echo", 4) == 0)
		|| ft_strlen(input) >= 5 && ft_strncmp(input, "echo ", 5) == 0)
		ft_echo(input);
	else if (ft_strlen(input) >= 3 &&
		ft_strncmp(input, "pwd", ft_strlen(input)) == 0)
	{	
		ft_pwd(input);
		//return ;
	}
	else if (ft_strlen(input) == 2 && ft_strncmp(input, "cd", ft_strlen(input)) == 0
			|| ft_strlen(input) >= 4 && ft_strncmp(input, "cd ", 3) == 0)
	{
		ft_cd(input, info);
		//return ;
	}
	else if (ft_strncmp(input, "env", ft_strlen(input)) == 0)
		ft_env(input);
	//these need to be finished:
	//if (ft_strncmp(input, "unset", 4) == 0)
	//	ft_unset(input);
	//if (ft_strncmp(input, "exit", 3) == 0)
	//	ft_exit(input);
	//if (ft_strncmp(input, "export", 5) == 0)
	//	ft_exit(input);
	else
		ft_othersimples(input, info);
	//if (i == -1) //execve will return -1 if the command doesn't exist, so trying to use this to return the correct error message
	//{	
	//	printf("%s", input);
	//	printf(": command not found\n");
		//return ;
	//}
}

//checks if there is a pipe in the command line
//if pipe, then sends input to the pipe fucntions
//returns true if pipe and inputs function moves to the next command
bool	ft_checkpipe(char *arraystring, bool h, int i)
{
	while (arraystring[i] != '\0')
	{
		if (arraystring[i] == '|')
		{
			//pipeprep(arraystring);
			h = true;
		}
		i++;
	}
	return (h);
}

//checks if there is a redirection and no pipe in command line
//if yes, sends to appropriate functions
//and returns true so moving to the next command
bool	ft_checkredirection(char *arraystring, bool h, int i)
{
	while (arraystring[i] != '\0')
	{
		if (arraystring[i] == '<' || arraystring[i] == '>')
		{
			h = true;
			if (arraystring[i + 1] == '<' || arraystring[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (h);
}

/*int	ft_initialcat(char **inputs, t_info **info)
{
	char	**catcheck;
	int	i;
	char	*newcommand;
	char	*pass;
	
	i = 0;
	catcheck = ft_split(inputs[0], '|');
	//printf("catcheck[0] == %s\n", catcheck[0]);
	while (catcheck[i] != NULL)
	{
		catcheck[i] = ft_strtrim(catcheck[i], " ");
		i++;
	}
	i = 0;
	while (ft_strlen(catcheck[i]) >= 2
		&& ft_strncmp(catcheck[i], "cat", 3) == 0)
		i++;
	//printf("cat number ==%d\n", i);
	//printf("catcheck[i] == %s\n", catcheck[i]);
	if (catcheck[i] == NULL || i == 0)
	{
		ft_freearray(catcheck);
		return (0);
	}
	newcommand = malloc(sizeof(char *) * 1);
	newcommand[0] = '\0';
	while(catcheck[i] != NULL)
	{
		if (catcheck[i + 1] != NULL)
		{
			catcheck[i] = ft_strjoin(catcheck[i], " | ", 8);
			newcommand = ft_strjoin(newcommand, catcheck[i], 2);
		}
		else
			newcommand = ft_strjoin(newcommand, catcheck[i], 2);
		i++;
	}
	ft_freearray(catcheck);
	pass = (*info)->inputs[0];
	inputs[0] = newcommand;
	free(pass);
	return (i - 1);
}*/

//this function asuumes that it is being passed a string representation of the command line with no errors
//this function performs minimal parsing and divides the command line input into an array
//the command line input is split at ';' only - 
//this should allow for complex pipe commands to be processed properly e.g. if they also involve redirection
//or multiple pipes
//have adapted strtrim to free the input
int	ft_inputs(char *input, t_info **info)
{
	char	**pass;
	int	i;
	bool	h;
	int	j;
	int	status;
	int	icats;
	
	h = false;
	i = 0;
	j = 0;
	if ((*info)->inputs)
		ft_freearray((*info)->inputs);
	(*info)->inputs = ft_split(input, ';');
	free(input);
	while ((*info)->inputs[i] != NULL)
	{
		(*info)->inputs[i] = ft_strtrim((*info)->inputs[i], " ");
		(*info)->inputs = ft_checkheredoc((*info)->inputs, info);
		//icats = ft_initialcat((*info)->inputs, info);
		//printf("(*info)->inputs[0] == %s\n", (*info)->inputs[0]);
		//heredoc has to be moved - things before it are executed e.g. ls > test1 and other simple redirections 
		if ((*info)->inputs == NULL)
			break ;
		h = ft_checkpipe((*info)->inputs[i],h, j);
		if (h == true)
			pipeprep((*info)->inputs[i], info);
		if (h == false)
		{
			h = ft_checkredirection((*info)->inputs[i], h, j);
			if (h == true)
				ft_redirectionmain((*info)->inputs[i], info);
		}
		if (h == false)
			ft_siminput((*info)->inputs[i], info);
		//ft_checkheredoc((*info)->inputs, info);
		h = false;
		i++;
	}
	if ((*info)->inputs)
		ft_freearray((*info)->inputs);
	return (0);
}
