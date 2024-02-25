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
