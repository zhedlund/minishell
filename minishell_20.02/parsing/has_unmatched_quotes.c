/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_unmatched_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:34:53 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/21 15:35:40 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

int has_unmatched_quotes(char *argv[])
{
	char	*str;
    int		single_quotes;
	int		double_quotes;
	int		i;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
    while (argv[i] != NULL)
    {
        str = argv[i];
        while (*str)
        {
			if (*str == '\"')
				double_quotes++;
			if (*str == '\'')
                single_quotes++;
            str++;
        }
		i++;
    }
	if ((single_quotes % 2 != 0) || (double_quotes % 2 != 0))
    	return (1);
	return (0);
}

