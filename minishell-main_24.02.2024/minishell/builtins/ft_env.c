/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:26:44 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/25 15:28:43 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

void	get_env(t_env **head)
{
	extern char	**environ;
	int			i;
	t_env		*temp;
	t_env		*node;

	i = 1;
	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		perror("malloc");
	node->field = ft_strdup(environ[0]);
	*head = node;
	while (environ[i] != NULL)
	{
		temp = (t_env *)malloc(sizeof(t_env));
		if (!temp)
			exit (1);
		temp->field = ft_strdup(environ[i]);
		node->next = temp;
		temp->prev = node;
		node = temp;
		node->next = NULL;
		i++;
	}
	temp = *head;
	temp->prev = node->next;
}

char	*ft_findvalue(char *name, t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp != NULL)
    {
        if (ft_strncmp(temp->field, name, ft_strlen(name)) == 0)
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		return (""); //does this always work, need to check with debugging statements removed
	return(temp->field);
}

void	ft_env(char *arraystring, t_env **head, t_info **info, t_exec *exec_cmd)
{
	t_env	*temp;

	temp = *head;
	if (exec_cmd->argv[1] != NULL)
	{
		ft_putstr_fd("env with no options or arguments thanks\n", 2);
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
