/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:26:44 by jelliott          #+#    #+#             */
/*   Updated: 2024/03/26 16:06:08 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_es(char **cmdargs, t_exec *exec_cmd, t_env **head, t_info **info)
{
	int		n;

	n = 1;
	while (cmdargs[1][n] != '\0')
	{
		if (cmdargs[1][n] != 'n')
			break ;
		n++;
	}
	if (cmdargs[1][n] == '\0')
		ft_minusndecide(head, info, exec_cmd);
}

int	ft_validsub(char *check)
{
	ft_putstr_fd("Minishell: export: '", 2);
	ft_putstr_fd(check, 2);
	return (2);
}

void	ft_env(t_env **head, t_info **info, t_exec *exec_cmd)
{
	t_env	*temp;

	temp = *head;
	if (exec_cmd->argv[1] != NULL)
	{
		ft_putstr_fd("env with no options or arguments thanks\n", 2);
		ft_multifree(head, info, exec_cmd);
		exit(127);
	}
	while (temp != NULL)
	{
		printf("%s\n", temp->field);
		temp = temp->next;
	}
	ft_multifree(head, info, exec_cmd);
	exit(0);
}
