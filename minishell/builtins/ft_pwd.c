/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:24:21 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/19 21:10:23 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	ft_multifree(t_env **head, t_info **info, t_exec *exec_cmd)
{
	int			check;
	char		**cmdargs;

	cmdargs = exec_cmd->argv;
	check = 0;
	rl_clear_history();
	while (cmdargs[check] != NULL)
	{
		free (cmdargs[check]);
		check++;
	}
	ft_freelist(head);
	free((*info));
	free(exec_cmd);
}

void	ft_pwd(t_env **head, t_info **info, t_exec *exec_cmd)
{
	char	store[PATH_MAX];
	char	*path;
	int		i;

	i = 0;
	path = getcwd(store, sizeof(store));
	if (path)
	{
		while (path[i] != '\0')
		{
			write(1, &path[i], 1);
			i++;
		}
	}
	else
		printf("%s", strerror(errno));
	write(1, "\n", 1);
	(*info)->exitstatus = 0;
	if ((*info)->inchild == true)
		ft_multifree(head, info, exec_cmd);
	else
		ft_multifree(head, info, exec_cmd);
	exit(0);
}
