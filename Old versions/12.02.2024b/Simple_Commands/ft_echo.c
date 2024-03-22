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
void	ft_printout(int a, char **cmdargs, t_info **info)
{
		while (cmdargs[a] != NULL)
		{
			if (ft_strlen("$?") == ft_strlen(cmdargs[a])
				&& ft_strncmp(cmdargs[a],"$?", ft_strlen("$?")) == 0)
					printf("%d", (*info)->exitstatus);
			else
				printf("%s", cmdargs[a]);
			if (cmdargs[a + 1] != NULL)
				printf(" ");
			a++;
		}
}

void    ft_echo(char *arraystring, char **cmdargs, t_env **head, t_info **info)
{
	int	a;
	bool	newline;

	newline = true;
	a = 1;
	if (cmdargs[1] == NULL)
		write(1, "\n", 1);
	if (cmdargs[1][0] == '-' && cmdargs[1][1] == 'n')
	{
		newline = false;
		a = 2;
	}
	if (newline == false && cmdargs[2] == NULL)
			write(1, "\n", 1);
	else
		ft_printout(a, cmdargs, info);
	if (newline == true)
		printf("\n");
}