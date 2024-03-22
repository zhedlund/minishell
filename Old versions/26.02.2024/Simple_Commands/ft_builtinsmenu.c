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

int	ft_builtinsmenu(char *argv, t_env **head)
{
	int	i;
	
	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == '|' || argv[i] == '>' || argv[i] == '<')
			return (1);
		i++;
	}
	i = 0;
	if (ft_strlen(argv) >= 2
		&& ft_strncmp(argv, "cd", 2) == 0)
		return (ft_cd(argv));
	else if (ft_strlen(argv) >= 3 
		&& ft_strncmp(argv, "env", 3) == 0)
		return (ft_env(argv, head));
	else if (ft_strlen(argv) >= 4 
		&& ft_strncmp(argv, "unset", 4) == 0)
		return (ft_unset(argv, head));
	else if (ft_strlen(argv) >= 3 
		&& ft_strncmp(argv, "exit", 3) == 0)
		printf("exit command\n");
		//return (ft_exit(input));
	else if (ft_strlen(argv) >= 5 
		&& ft_strncmp(argv, "export", 5) == 0)
		printf("export command\n");
		//return (ft_export(input));
		return (1);
}
