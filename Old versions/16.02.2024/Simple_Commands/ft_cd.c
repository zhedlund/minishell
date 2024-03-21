/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:25:07 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:25:09 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"
#include <limits.h>

char	*ft_cdsub(char *arraystring)
{
	char	*locate;
	int	j;
	int	i;

	j = 0;
	i = 3;
	while (arraystring[j] != '\0')
		j++;
	j -= 3;
	locate = (char *)malloc(sizeof(char) * (j + 1));
	if (!locate)
		return (NULL);
	i = 3;
	j = 0;
	while (arraystring[i] != '\0')
	{
		locate[j] = arraystring[i];
		j++;
		i++;
	}
	locate[j] = '\0';
	return (locate);
}

char	*ft_home(char *locate)
{
	locate = ft_strdup(getenv("HOME"));
	if (locate == NULL || *locate == '\0')
	{
		printf("cd HOME not set\n");
		return (NULL);
	}
	return(locate);
}

char	*ft_path(char *former)
{
	char	store[PATH_MAX];
	char	*path;
	int	i;
	char	*output;
	
	path = getcwd(store, sizeof(store));
	i = ft_strlen(path);
	output = (char *)malloc(sizeof(char) * (i + 1));
	output[i] = '\0';
	output = strcpy(output, path);
	//if doesn't work
	//path = getenv(path);
	if (!former)
		return (output);
	else
		free(former);
	return (output);
}

char	*ft_backone(char *locate)
{
	int	i;
	int	j;
	char	*output;
	
	i = 0;
	j = 0;
	output = NULL;
	if (locate[i] == '/' && locate[1] == '\0')
		return (locate);
	printf("%s\n", locate);
	while (locate[i] != '\0')
		i++;
	while (locate[i] != '/')
		i--;
	if (ft_strlen(locate) > 5)
		i--;
	output = malloc(sizeof(char) * (i + 2));
	//error??
	while (j <= i)
	{
		output[j] = locate[j];
		j++;
	}
	output[j] = '\0';
	return (output);
}

int   ft_cd(char *arraystring)
{
	char	*locate;
	char	*hold;
	char 	**cdpath;
	
	locate = NULL;
	locate = ft_path(locate);
	hold = locate;
	if (ft_strlen(arraystring) == 2 ||
		ft_strlen(arraystring) == 4 
			&& ft_strncmp(arraystring, "cd ~", 5) == 0)
		locate = ft_home(locate);
	else if (ft_strlen(arraystring) == 4 
		&& ft_strncmp(arraystring, "cd .", 5) == 0)
	{	
		chdir(locate);
		free (locate);
		return (0);
	}
	else if (ft_strlen(arraystring) == 5 &&
		strncmp(arraystring, "cd ..", 5) == 0)
		locate = ft_backone(locate);
	//else if (ft_strlen(arraystring) == 4 
	//	&& ft_strncmp(arraystring, "cd -", 5) == 0)
	//	printf("need to play with env variable");
		//locate = ft_strdup(getenv("OLDPWD"));
	else
		locate = ft_cdsub(arraystring);
	if (chdir(locate) != 0)
		perror("chdir");
	if (locate)
		free(locate);
	if (hold)
		free(hold);
	return (0);
}
