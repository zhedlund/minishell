/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:26:44 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:26:46 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"
//env might be used alone - prints the entire environment
//or with a specified variable, in which case want to print info pertaining to that
//this function primarily deals with env being used alone
void   ft_env(char *arraystring, t_env **head, t_info **info, t_exec *exec_cmd)
{
	t_env	*temp;

	temp = *head;
	if (exec_cmd->argv[1] != NULL)
	{
		write(2, "env with no options or arguments thanks\n", ft_strlen("env with no options or arguments thanks\n"));
		ft_multifree(arraystring, head, info, exec_cmd);
		exit(0);
	}
	while (temp != NULL)
	{
		printf("%s\n", temp->field);
		temp = temp->next;
	}
	(*info)->exitstatus = 0;
	{
		ft_multifree(arraystring, head, info, exec_cmd);
		exit(0);
	}
}