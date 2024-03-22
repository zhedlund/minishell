/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:22:47 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/19 20:36:09 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	ft_echoend(t_env **head, t_info **info, t_exec *exec_cmd)
{
	(*info)->exitstatus = 0;
	ft_multifree(head, info, exec_cmd);
	exit(0);
}

int	ft_minusnfun(char *cmdarg)
{
	int	i;

	i = 1;
	if (ft_strlen(cmdarg) < ft_strlen("-n"))
		return (false);
	if (ft_strncmp(cmdarg, "-n", ft_strlen("-n")) != 0)
		return (false);
	while (cmdarg[i] != '\0')
	{
		if (cmdarg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	ft_printout(int a, char **cmdargs, bool newline)
{
	if (ft_minusnfun(cmdargs[a]) == true)
		a++;
	while (cmdargs[a] != NULL)
	{
		if (cmdargs[a][0] == 92 
			&& cmdargs[a][1] == '\0')
		{
			a++;
			printf(" ");
		}
		printf("%s", cmdargs[a]);
		if (cmdargs[a + 1] != NULL)
			printf(" ");
		a++;
	}
	if (newline == true)
		printf("\n");
}

void	ft_minusndecide(t_env **head, t_info **info, t_exec *exec_cmd)
{
	int		a;
	bool	newline;
	char	**cmdargs;

	cmdargs = exec_cmd->argv;
	a = 1;
	newline = false;
	while (cmdargs[a] != NULL)
	{
		if (ft_minusnfun(cmdargs[a]) == true)
			a++;
		else
		{
			ft_printout(a, cmdargs, newline);
			ft_echoend(head, info, exec_cmd);
		}
	}
	if (cmdargs[2] == NULL)
		newline = true;
	if (newline == false)
		a -= 1;
	ft_printout(a, cmdargs, newline);
	ft_echoend(head, info, exec_cmd);
}

void	ft_echo(t_exec *exec_cmd, t_env **head, t_info **info)
{
	bool	newline;
	char	**cmdargs;
	int		a;
	int		n;

	n = 1;
	a = 1;
	newline = true;
	cmdargs = exec_cmd->argv;
	if (cmdargs[1] == NULL)
	{
		printf("\n");
		exit(0);
	}
	if (cmdargs[1][0] == '-' && cmdargs[1][1] == 'n')
	{
		while (cmdargs[1][n] != '\0')
		{
			if (cmdargs[1][n] != 'n')
				break ;
			n++;
		}
		if (cmdargs[1][n] == '\0')
			ft_minusndecide(head, info, exec_cmd);
	}
	ft_printout(a, cmdargs, newline);
	ft_echoend(head, info, exec_cmd);
}
