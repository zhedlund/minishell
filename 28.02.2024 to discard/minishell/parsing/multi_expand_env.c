/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_expand_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:34:24 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/28 11:34:27 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*ft_multitostring(char **toname)
{
	char	*string;
	int		a;

	a = 2;
	string = ft_strjoin(toname[0], toname[1]);
	while (toname[a] != NULL)
	{
		string = ft_strjoin(string, toname[a]);
		a++;
	}
	return (string);
}

char	*ft_multiexpand(char *name, t_env **head)
{
	char	**expansionarray;
	int		a;
	char	*hold;

	a = 0;
	expansionarray = ft_split(name, '$');
	while (expansionarray[a] != NULL)
	{
		hold = ft_decidevalue(expansionarray[a], head);
		if (hold != NULL)
		{
			free (expansionarray[a]);
			expansionarray[a] = hold;
		}
		a++;
	}
	hold = ft_multitostring(expansionarray);
	printf("hold == %s\n", hold);
	ft_freearray(expansionarray);
	return (hold);
}

bool	ft_multiple(char *name)
{
	int	a;
	int	expands;

	a = 0;
	expands = 0;
	while (name[a] != '\0')
	{
		if (name[a] == '$' && name[a] != '\0' && name[a] != '?')
			expands++;
		a++;
	}
	if (expands != 0)
		return (true);
	return (false);
}
