/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:04:37 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/02 11:04:39 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Builtins.h"
#include "Libft/libft.h"
#include <sys/ioctl.h>
 //have noticed that if the invalid heredoc is first, then don't execute the later heredoc

char	*ft_extracthd(char **tmp, char *newcmdline, int i)
{
	while (tmp[i] != NULL)
	{
		if (ft_strncmp(tmp[i], "cat", 2) == 0
			&& ft_strncmp(tmp[i + 1], "<<", 1) == 0)
			i++;
		if (ft_strncmp(tmp[i], "<<", 1) == 0)
			i += 2;
		if (tmp[i] == NULL)
			break ;
		tmp[i] = ft_strjoin(tmp[i], " ", 2);
		newcmdline = ft_strjoin(newcmdline, tmp[i], 2);
		i++;
	}
	return (newcmdline);
}

char	*ft_newinputsarray(char **tmp)
{
	int	i;
	char	*newcmdline;

	newcmdline = malloc(sizeof(char) * 1);
	newcmdline[0] = '\0';
	i = 0;
	newcmdline = ft_extracthd(tmp, newcmdline, i);
	if (ft_strlen(newcmdline) == 0)
	{
		free(newcmdline);
		return (NULL);
	}
	return (newcmdline);
}

char	**ft_heredocarray(int heredoc, char **inputs)
{
	int	i;
	int	j;
	char	**hdarray;

	i = 0;
	j = 0;
	hdarray = (char **)malloc(sizeof(char *) * (heredoc + 1));
	hdarray[heredoc] = NULL;
	while (inputs[i] != NULL)
	{
		if (ft_strncmp(inputs[i], "<<", 1) == 0)
		{
			hdarray[j] = ft_strdup(inputs[i + 1], 0);
			j++;
		}
		i++;
	}
	return (hdarray);
}
