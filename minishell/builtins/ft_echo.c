/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:22:47 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/25 21:31:39 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_printout(int a, char **cmdargs, bool newline)
{
	while (cmdargs[a] != NULL)
	{
		printf("%s", cmdargs[a]);
		if (cmdargs[a + 1] != NULL)
			printf(" ");
		a++;
	}
	if (newline == true)
		printf("\n");
}

void	ft_echo(t_exec *exec_cmd, t_env **head, t_info **info)
{
	int		a;
	bool	newline;
	char	**cmdargs;

	newline = true;
	a = 1;
	cmdargs = exec_cmd->argv;
	if (cmdargs[1][0] == '-' && cmdargs[1][1] == 'n')
	{
		newline = false;
		while (cmdargs[a] != NULL)
			a++;
		if (cmdargs[2] == NULL)
			newline = true;
		if (newline == false)
			a -= 1;
	}
	ft_printout(a, cmdargs, newline);
	(*info)->exitstatus = 0;
	ft_multifree(NULL, head, info, exec_cmd);
	exit(0);
}
