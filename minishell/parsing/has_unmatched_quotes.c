/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unmatched_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:34:53 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/25 21:34:29 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

const char	*ft_arraytostring(char **array)
{
	char *string;
	char	*hold;
	int	a;

	a = 1;
	if (array[a] != NULL)
		string = ft_strjoin(array[0], " ");
	else
		return (ft_strdup(array[0]));
	while (array[a] != NULL)
	{
		if (array[a + 1] != NULL)
			hold = ft_strjoin(array[a], " ");
		else
			hold = ft_strdup(array[a]);
		string = ft_strjoin(string, hold);
		a++;
	}
	return (string);
}

bool	ft_mix(char *possmixed)
{
	int	a;
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

const char	*ft_countquotes(char *before, char *input)
{
	int	a;
	int	i;
	char **inputarray;
	char	**inputbefore;
	bool	moveone;
	char	dqq;
	char	*dq;
	char	*qq;
	char	q;

	q = 39;
	qq = &q;
	dqq = 34;
	dq = &dqq;
	inputarray = ft_split(input, ' ');
	inputbefore = ft_split(before, ' ');
	a = 0;
	i = 0;
	moveone = false;
	while (inputarray[a] != NULL)
	{
		while (inputarray[a][i] != '\0')
		{
			if (inputarray[a][i] == '|'
				|| inputarray[a][i] == '<'
				||inputarray[a][i] == '>')
				moveone = true;
			i++;
		}
		if (moveone == false && ft_identical(inputbefore[a], inputarray[a]) == true
			&& ft_mix(inputarray[a]) == false)
		{
			if (inputarray[a][0] == 34)
				inputarray[a] = ft_strtrim(inputarray[a], dq);
			else if (inputarray[a][0] == 39)
				inputarray[a] = ft_strtrim(inputarray[a], qq);
		}
		moveone = false;
		a++;
		i = 0;
	}
	return(ft_arraytostring(inputarray));
}

bool	has_unmatched_quotes(const char *input)
{
	int			squote;
	int			dquote;
	int			in_single;
	int			in_double;

	squote = 0;
	dquote = 0;
	in_single = 0;
	in_double = 0;
	printf("input == %s\n", input);
	while (*input)
	{
		if (*input == '\'' && !in_double)
		{
			squote++;
			in_single = !in_single;
		}
		else if (*input == '"' && !in_single)
		{
			dquote++;
			in_double = !in_double;
		}
		input++;
	}
	return (in_single || in_double || (squote % 2 != 0) || (dquote % 2 != 0));
}
