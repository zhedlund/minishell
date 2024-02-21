/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:24:21 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/21 16:58:02 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

void    ft_pwd(char *arraystring, t_env **head, t_info **info, t_exec *exec_cmd)
{
	char	store[PATH_MAX]; // PATH_MAX in limits.h defines the maximum length of a path, usually 4096
	char	*path;
	int	i;
	
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
	ft_multifree(arraystring, head, info, exec_cmd);
	exit(0);
}