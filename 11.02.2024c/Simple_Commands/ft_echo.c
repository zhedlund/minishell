/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:22:47 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:22:49 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

//works for expansion
//still need to work out exit statuses
void    ft_echo(char *arraystring, char **cmdargs, t_env **head)
{
	int	a;
	bool	newline;

	newline = true;
	a = 1;
	if (cmdargs[1] == NULL)
		write(1, "\n", 1);
	else if (cmdargs[1][0] == '-' && cmdargs[1][1] == 'n')
	{
		newline = false;
		a = 2;
	}
	if (newline == false && cmdargs[2] == NULL)
			write(1, "\n", 1);
	else
	{
		while (cmdargs[a] != NULL)
		{
			printf("%s", cmdargs[a]);
			if (cmdargs[a + 1] != NULL)
				printf(" ");
			a++;
		}
	}
	if (newline == true)
		printf("\n");
}
