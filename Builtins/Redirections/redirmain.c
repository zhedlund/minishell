/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:33:00 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/19 11:33:02 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Builtins.h"

//is this last library legit?

//this function copes with commands that begin with the redirection sign
//these commands should just open/create documents etc.
void	ft_redirnocommand(char **redirarray)
{
	int	kind;
	char    *type;
	char    *command;
	char	*filename;
	
	ft_getfiledescriptor(redirarray[0], redirarray[1]);
}
/*
//this will probably be useful for heredoc also
int	ft_combinationwarnings(char **redirarray)
{
	int	i;
	
	i = 1;
	while (redirarray[i] != NULL)
	{
		if (redirarray[i][0] == '>' && redirarray[i][1] == '\0'
			 && redirarray[i + 2][0] == '<' && redirarray[i + 2][1] == '\0')
			return (1);
		if (redirarray[i][0] == '>' && redirarray[i][1] == '>'
			 && redirarray[i + 2][0] == '<' && redirarray[i + 2][1] == '\0')
			return (2);
		i += 2;
	}
	return (0);
}*/
char	**ft_complexcommand(char **redirarray)
{
	char	*complexcommand;
	char	**outputarr;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (redirarray[i] != NULL)
		i++;
	if (i == 3)
		return (redirarray);
	i = 0;
	complexcommand = malloc(sizeof(char) * 1);
	complexcommand[0] = '\0';
	while (redirarray[i][0] != '<' && redirarray[i][0] != '>')
	{
		redirarray[i] = ft_strjoin(redirarray[i], " ", 2);
		complexcommand = ft_strjoin(complexcommand, redirarray[i], 2);
		i++;
	}
	while (redirarray[j] != NULL)
		j++;
	outputarr = (char **)malloc(sizeof(char *) * (j - i + 1));
	outputarr[j - i + 1] = NULL;
	outputarr[0] = complexcommand;
	//free(complexcommand);
	i = 1;
	while (outputarr[i] != NULL)
	{
		outputarr[i] = ft_strdup(redirarray[i], 0);
		outputarr[i] = ft_strdup(redirarray[i + 1], 0);
		
	}
	ft_freearray(redirarray);
	return(outputarr);
	
}

char	**ft_redirarray(char **redirarray, int count)
{
	char	**outarray;
	int	i;
	int	j;
	char	*complexcommand;

	i = 0;
	j = 0;
	complexcommand = malloc(sizeof(char) * 1);
	complexcommand[0] = '\0';
	outarray = (char **)malloc(sizeof(char *) * (count + (count + 1)));
	outarray[count + count] = NULL;
	while (redirarray[i] != NULL)
	{
		if (redirarray[i][0] == '<' || redirarray[i][0] == '>')
		{
			outarray[j] = ft_strdup(redirarray[i], 0);
			j++;
			i++;
		}
		while (redirarray[i] != NULL && redirarray[i][0] != '<' && redirarray[i][0] != '>')
		{
			redirarray[i] = ft_strjoin(redirarray[i], " ", 2);
			printf("redirarray[i] == %s\n", redirarray[i]);
			complexcommand = ft_strjoin(complexcommand, redirarray[i], 2);
			printf("complexcommand == %s\n", complexcommand);
			i++;
		}
		outarray[j] = complexcommand;
		printf("outarray[j] == %s\n", outarray[j]);
		if (redirarray[i] == NULL)
			break ;
		complexcommand = NULL;
		complexcommand = malloc(sizeof(char) * 1);
		complexcommand[0] = '\0';
		//outarray[j + 1] = ft_strdup(redirarray[i], 0);
		j++;
		//i++;
	}
	ft_freearray(redirarray);
	printf("outarray[0] == %s\n", outarray[0]);
	printf("outarray[1] == %s\n", outarray[1]);
	printf("outarray[2] == %s\n", outarray[2]);
	return (outarray);
}

//- this function splits the command string input into an array
//- depending on type of command it forks a child process - skip forking if no command 
//e.g. > file.txt just overwrites file's contents or the open function will create file.txt if it dosen't exist
//- within the child process, further functions are called to set the input/out of the child process
//- end by freeing the array we began by creating
//- throughout check for things going wrong
int	ft_redirectionmain(char *arraystring, t_info **info)
{
	char    **redirarray;
	int i;
	int	count;
	char	*command;
	int	combi;
	char	*hold;
	
	i = 0;
	count = 0;
	redirarray = ft_split(arraystring, ' ');
	while (redirarray[i] != NULL)
	{
		redirarray[i] = ft_strtrim(redirarray[i], " ");
		if (redirarray[i][0] == '<' || redirarray[i][0] == '>')
			count++;
		i++;
	}
	redirarray = ft_redirarray(redirarray, count);
	printf("redirarray[0] == %s\n", redirarray[0]);
    if (redirarray[0][0] == '>' || redirarray[0][0] == '<')
	ft_redirnocommand(redirarray);	
    else
    {
        //with these assignments - potential worry if the command is more than a single word
        //e.g. ls filename > newfile.txt
        //don't think longer is possible
        //might be further problems is there is multiple after redirection sign comamnds
        //printf("checking for complexcommand\n");
        //redirarray = ft_complexcommand(redirarray);
        command = redirarray[0];
	if (count == 1)
		ft_simpleredir(redirarray, info);
	else if (count == 2)
		ft_doubleredirection(redirarray, info);
	else
		ft_longredir(redirarray, command, info);
    }
    if (redirarray)
	    ft_freearray(redirarray);
    //free(command);
    return (0);
}
