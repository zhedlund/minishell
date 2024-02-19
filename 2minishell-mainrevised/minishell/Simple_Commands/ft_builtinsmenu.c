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
void	ft_builtinsmenu(char *argv, char **cmdinfo, t_env **head, t_info **info)
{
	(*info)->inchild = false;
	if (ft_strlen("cd") == ft_strlen(argv) 
		&& ft_strncmp(argv, "cd", ft_strlen(argv)) == 0)
		ft_cd(cmdinfo, head, info);
	else if (ft_strlen("unset") == ft_strlen(argv) 
		&& ft_strncmp(argv, "unset", ft_strlen(argv)) == 0)
		ft_unset(argv, cmdinfo, head, info);
	else if (ft_strlen("exit") == ft_strlen(argv) 
		&& ft_strncmp(argv, "exit", ft_strlen(argv)) == 0)
		ft_exit(cmdinfo, head, info);
	else if (ft_strlen("export") == ft_strlen(argv) 
		&& ft_strncmp(argv, "export", ft_strlen(argv)) == 0)
		ft_export(cmdinfo, head, info);
	else if(argv != NULL)
	{
		write(2, "Command not found: ", ft_strlen("Command not found: ")); 
		write(2, argv, ft_strlen(argv));
		write(2, "\n", ft_strlen("\n"));
		ft_freelist(head);
		ft_freearray(cmdinfo);
		free(*info);
		exit(127);
	}
}
