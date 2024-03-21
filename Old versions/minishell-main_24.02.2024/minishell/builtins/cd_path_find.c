/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:24:33 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/23 17:24:36 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

char	*ft_cdsub(char *arraystring)
{
	char	*locate;
	int		j;

	j = 0;
	while (arraystring[j] != '\0')
		j++;
	locate = (char *)malloc(sizeof(char) * (j + 1));
	if (!locate)
		return (NULL);
	locate[j] = '\0';
	j = 0;
	while (arraystring[j] != '\0')
	{
		locate[j] = arraystring[j];
		j++;
	}
	locate[j] = '\0';
	return (locate);
}

char	*ft_path(char *former)
{
	char	store[PATH_MAX];
	char	*path;
	int		i;
	char	*output;

	path = getcwd(store, sizeof(store));
	i = ft_strlen(path);
	output = (char *)malloc(sizeof(char) * (i + 1));
	output[i] = '\0';
	output = ft_strcpy(output, path);
	if (!former)
		return (output);
	else
		free(former);
	return (output);
}

char	*ft_backone_sub(char *locate, int i)
{
	int		j;
	char	*output;

	j = 0;
	output = malloc(sizeof(char) * (i + 2));
	if (!output)
		exit(1);
	while (j <= i)
	{
		output[j] = locate[j];
		j++;
	}
	output[j] = '\0';
	return (output);
}

char	*ft_backone(char *locate)
{
	int		i;
	char	*output;

	i = 0;
	locate = ft_path(NULL);
	output = NULL;
	i = ft_strlen(locate);
	while (locate[i] != '/')
		i--;
	if (ft_strlen(locate) > 5)
		i--;
	output = ft_backone_sub(locate, i);
	free(locate);
	return (output);
}
