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
	if (ft_strlen(argv) >= 2
		&& ft_strncmp(argv, "cd", 2) == 0)
		ft_cd(argv, cmdinfo, head);
	else if (ft_strlen(argv) >= 3 
		&& ft_strncmp(argv, "env", 3) == 0)
		ft_env(argv, head);
	else if (ft_strlen(argv) >= 4 
		&& ft_strncmp(argv, "unset", 4) == 0)
		ft_unset(argv, cmdinfo, head);
	else if (ft_strlen(argv) >= 3 
		&& ft_strncmp(argv, "exit", 3) == 0)
		ft_exit(argv, cmdinfo, head);
		//return (ft_exit(input));
	else if (ft_strlen(argv) >= 5 
		&& ft_strncmp(argv, "export", 5) == 0)
		ft_export(argv, cmdinfo, head);
	//add echo and pwd
}
