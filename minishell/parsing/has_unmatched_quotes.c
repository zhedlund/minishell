/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unmatched_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:34:53 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/21 22:29:23 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

bool	has_unmatched_quotes(const char *input)
{
	int			single_quotes;
	int			double_quotes;
	int			in_single_quotes;
	int			in_double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
    while (*input)
	{
        if (*input == '\'' && !in_double_quotes)
		{
            single_quotes++;
            in_single_quotes = !in_single_quotes;
        }
		else if (*input == '"' && !in_single_quotes)
		{
            double_quotes++;
            in_double_quotes = !in_double_quotes;
        }
        input++;
    }
    return (in_single_quotes || in_double_quotes
		|| (single_quotes % 2 != 0) || (double_quotes % 2 != 0));
}
