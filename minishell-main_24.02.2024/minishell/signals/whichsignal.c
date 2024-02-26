/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whichsignal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:27:18 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/26 16:27:20 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

int	ft_firstcommandcheck(char *buf, t_info **info)
{
	char	**firstcommandarray;
	int		i;

	i = 0;
	firstcommandarray = ft_split(buf, '|');
	firstcommandarray = ft_arraytrim(firstcommandarray);
	if (ft_identical(firstcommandarray[0], "cat") == true
		|| ft_identical(firstcommandarray[0], "wc") == true
		|| ft_identical(firstcommandarray[0], "wc -l") == true
		|| ft_greponearguement(firstcommandarray[0]) == true)
	{
		ft_othercommands(firstcommandarray, info);
		ft_freearray(firstcommandarray);
		return (2);
	}
	ft_freearray(firstcommandarray);
	return (0);
}

bool	ft_greponearguement(char *totest)
{
	char	**greptestarray;

	if (ft_strlen("grep ") < ft_strlen(totest)
		&& ft_strncmp("grep ", totest, ft_strlen("grep ")) == 0)
	{
		greptestarray = ft_split(totest, ' ');
		if (greptestarray[1] != NULL 
			&& greptestarray[1][0] != '<'
			&& greptestarray[1][0] != '>'
			&& greptestarray[2] == NULL)
		{
			ft_freearray(greptestarray);
			return (true);
		}
		ft_freearray(greptestarray);
	}
	return (false);
}

void	ft_othercommands(char **firstcommandarray, t_info **info)
{
	int	i;

	i = 1;
	while (firstcommandarray[i] != NULL)
	{
		if (ft_identical(firstcommandarray[i], "cat") == false
			&& ft_identical(firstcommandarray[i], "wc") == false
			&& ft_greponearguement(firstcommandarray[i]) == false)
		{
			(*info)->firstcommandmix = true;
			return ;
		}
		i++;
	}
	(*info)->firstcommandmix = false;
}

char	**ft_arraytrim(char **totrim)
{
	int		i;

	i = 0;
	while (totrim[i] != NULL)
	{
		totrim[i] = ft_strtrim(totrim[i], " ");
		i++;
	}
	return (totrim);
}
