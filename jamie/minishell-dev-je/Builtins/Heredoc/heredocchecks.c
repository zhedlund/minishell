/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocchecks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:23:57 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/06 17:24:00 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Builtins.h"
#include "../Libft/libft.h"
#include <sys/ioctl.h>

char	*ft_extracthd(char **tmp, char *newcmdline, int i, t_info **info)
{
	int	copy;
	
	copy = (*info)->catcount;
	while (tmp[i] != NULL)
	{
		while (ft_strncmp(tmp[i], "<<", ft_strlen(tmp[i])) != 0)
		{
			if (ft_strncmp(tmp[i], "cat", ft_strlen(tmp[i])) == 0 
				&& ft_strncmp(tmp[i + 1], "<<", ft_strlen(tmp[i])) == 0 )
				break ;
			else
				tmp[i] = ft_strjoin(tmp[i], " ", 2);
				newcmdline = ft_strjoin(newcmdline, tmp[i], 2);
			i++;
		}
		copy--;
		if (ft_strncmp(tmp[i], "cat", ft_strlen(tmp[i])) == 0)
			i++;
		if (ft_strncmp(tmp[i], "<<", ft_strlen(tmp[i])) == 0 && (tmp[i + 2] != NULL)
			&& ft_strncmp(tmp[i + 2], "|", ft_strlen(tmp[i + 2])) == 0)
			i += 3;
		if (ft_strncmp(tmp[i], "<<", ft_strlen(tmp[i])) == 0)
			i += 2;
		if (tmp[i] == NULL)
			break ;
		if (copy == 0)
		{
			tmp[i] = ft_strjoin(tmp[i], " ", 2);
			newcmdline = ft_strjoin(newcmdline, tmp[i], 2);
		}
		i++;
	}
	return (newcmdline);
}

char	*ft_newinputsarray(char **tmp , t_info **info)
{
	int	i;
	char	*newcmdline;

	newcmdline = malloc(sizeof(char) * 1);
	newcmdline[0] = '\0';
	i = 0;
	newcmdline = ft_extracthd(tmp, newcmdline, i, info);
	if (ft_strlen(newcmdline) == 0)
	{
		free(newcmdline);
		return (NULL);
	}
	printf("newcmdline == %s\n", newcmdline);
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
