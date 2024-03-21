/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:46:47 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/27 19:46:50 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*ft_output(char *input, int d)
{
	int		a;
	char	*output;

	a = 0;
	output = malloc(sizeof(char) * (d + 1));
	d = 0;
	while (input[a] != '\0')
	{
		if (input[a] != 34)
		{
			output[d] = input[a];
			d++;
		}
		a++;
	}
	output[d] = '\0';
	return (output);
}

char	*ft_noquotes(char *input)
{
	char	*output;
	int		a;
	int		d;

	d = 0;
	a = 0;
	while (input[a] != '\0')
	{
		if (input[a] != 34)
			d++;
		a++;
	}
	output = ft_output(input, d);
	free(input);
	return (output);
}
