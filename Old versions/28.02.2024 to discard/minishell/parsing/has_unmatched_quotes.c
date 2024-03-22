/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unmatched_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:34:53 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/22 11:16:57 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

bool	ft_backtrim(char *input)
{
	int	i;

	i = ft_strlen(input);
	if (input[i - 1] == 34)
		return (true);
	return (false);
}

char	*ft_unquote(char *input)
{
	char	dqq;
	char	*dq;
	char	*qq;
	char	q;

	q = 39;
	qq = &q;
	dqq = 34;
	dq = &dqq;
	if (input[0] == 34)
		return (ft_strtrim(input, dq));
	if (ft_backtrim(input) == true)
		return (ft_strtrim(input, dq));
	else if (input[0] == 39)
	{
		if (ft_odd(input) == false)
			input = ft_strtrim(input, qq);
	}
	return (input);
}

const char	*ft_countquotes(char *before, char *input)
{
	int			a;
	char		**inputarray;
	char		**inputbefore;
	bool		moveone;
	const char	*sendback;

	inputarray = ft_split(input, ' ');
	inputbefore = ft_split(before, ' ');
	a = 0;
	moveone = false;
	while (inputarray[a] != NULL)
	{
		moveone = ft_moveone(inputarray[a]);
		if (moveone == false 
			&& ft_identical(inputbefore[a], inputarray[a]) == true
			&& ft_mix(inputarray[a]) == false)
			inputarray[a] = ft_unquote(inputarray[a]);
		a++;
	}
	ft_freearray(inputbefore);
	sendback = ft_arraytostring(inputarray);
	if (inputarray)
		ft_freearray(inputarray);
	return (sendback);
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
