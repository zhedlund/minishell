/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:10:00 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/15 18:10:02 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"
void	ft_builtinsmenu(char *argv, char **cmdinfo, t_env **head)
{
	if (ft_strlen("cd") == ft_strlen(argv) 
		&& ft_strncmp(argv, "cd", ft_strlen(argv)) == 0)
		ft_cd(argv, cmdinfo, head);
	//else if (ft_strlen(argv) >= 3 
	//	&& ft_strncmp(argv, "env", 3) == 0)
	//	ft_env(argv, head);
	else if (ft_strlen("unset") == ft_strlen(argv) 
		&& ft_strncmp(argv, "unset", ft_strlen(argv)) == 0)
		ft_unset(argv, cmdinfo, head);
	else if (ft_strlen("exit") == ft_strlen(argv) 
		&& ft_strncmp(argv, "exit", ft_strlen(argv)) == 0)
		ft_exit(argv, cmdinfo, head);
	else if (ft_strlen("export") == ft_strlen(argv) 
		&& ft_strncmp(argv, "export", ft_strlen(argv)) == 0)
		ft_export(argv, cmdinfo, head);
	else if(argv != NULL)
	{
		//(*info)->exitstatus = 127;
		printf("Command not found: %s\n", argv);
	}
}
