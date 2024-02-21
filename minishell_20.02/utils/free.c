/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:48:51 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/21 16:58:19 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

//using errno to print the error message, but need to check if we are allowed to use this
//problem here that there is no variable to give - same with some other builtin functions
//this function uses getcwd to store the pwd in a string and then prints the string
void	ft_multifree(char *arraystring, t_env **head, t_info **info, t_exec *exec_cmd)
{
	int	check;
	char	**cmdargs;

	cmdargs = exec_cmd->argv;
	check = 1;
	rl_clear_history();
	if (arraystring == NULL)
		check = 0;
	while (cmdargs[check] != NULL)
	{
		free (cmdargs[check]);
		check++;
	}
	//if ((*head) != NULL)
		ft_freelist(head);
	//if ((*info) != NULL)
		free((*info));
	if (arraystring != NULL)
		free(arraystring);
	free(exec_cmd);
}

void	ft_freearray(char **tofree)
{
	int	i;
	
	i = 0;
	if(!tofree)
		return ;
	while(tofree[i] != NULL)
	{
		free(tofree[i]);
		//tofree[i] = NULL;
		i++;
	}
	free(tofree);
	//tofree = NULL;
}

void	ft_freelist(t_env **head)
{
	t_env	*node;
	t_env	*nodenext;

	node = (*head);
	while (node != NULL)
	{
		nodenext = (node->next);
		//printf("%d\n", node->field);
		free(node->field);
		free (node);
		node = NULL;
		node = nodenext;
	}
	node = NULL;
	nodenext = NULL;
	(*head) = NULL;
}
