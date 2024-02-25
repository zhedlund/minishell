/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:48:51 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/25 21:34:56 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freearray(char **tofree)
{
	int	i;

	i = 0;
	if (!tofree)
		return ;
	while (tofree[i] != NULL)
	{
		free(tofree[i]);
		i++;
	}
	free(tofree);
}

void	ft_freelist(t_env **head)
{
	t_env	*node;
	t_env	*nodenext;

	node = (*head);
	while (node != NULL)
	{
		nodenext = (node->next);
		free(node->field);
		free (node);
		node = NULL;
		node = nodenext;
	}
	node = NULL;
	nodenext = NULL;
	(*head) = NULL;
}

void	ft_multifree(char *a, t_env **head, t_info **info, t_exec *exec_cmd)
{
	int			check;
	char		**cmdargs;

	cmdargs = exec_cmd->argv;
	check = 1;
	rl_clear_history();
	if (a == NULL)
		check = 0;
	while (cmdargs[check] != NULL)
	{
		free (cmdargs[check]);
		check++;
	}
	ft_freelist(head);
	free((*info));
	if (a != NULL)
		free(a);
	free(exec_cmd);
}
