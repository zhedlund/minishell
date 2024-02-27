/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:10:58 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/27 20:11:01 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*ft_atossub(char **array, int a, char *string)
{
	char	*hold;
	char	*holdstring;
	
	if (array[a + 1] != NULL)
		hold = ft_strjoin(array[a], " ");
	else
		hold = ft_strdup(array[a]);
	holdstring = string;
	string = ft_strjoin(string, hold);
	free(hold);
	free(holdstring);
	return (string);
}

const char	*ft_arraytostring(char **array)
{
	char	*string;
	char	*hold;
	int		a;

	a = 1;
	if (array[0] != NULL)
	{
		hold = ft_strdup(array[0]);
		string = ft_strjoin(hold, " ");
		free (hold);
	}
	else
		return (ft_strdup(array[0]));
	while (array[a] != NULL)
	{
		string = ft_atossub(array, a, string);
		a++;
	}
	return (string);
}

bool	ft_mix(char *possmixed)
{
	int		a;
	bool	single;
	bool	dquote;

	single = false;
	dquote = false;
	a = 0;
	while (possmixed[a] != '\0')
	{
		if (possmixed[a] == 39)
			single = true;
		if (possmixed[a] == 34)
			dquote = true;
		a++;
	}
	if (single == true && dquote == true)
		return (true);
	else
		return (false);
}

bool	ft_odd(char *tocheck)
{
	int	a;

	a = 0;
	while (tocheck[a] == 39)
		a++;
	if ((a % 2) == 0)
		return (false);
	return (true);
}

bool	ft_moveone(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|'
			|| input[i] == '<'
			||input[i] == '>')
			return (true);
		i++;
	}
	return (false);
}
