/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:23:44 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:23:46 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	ft_list_start_end(t_env **head, t_env *temp, bool start)
{
	t_env	*passnext;
	t_env	*passprev;

	if (start == true)
	{
		*head = temp->next;
		(*head)->prev = temp->prev;
		free(temp->field);
		free(temp);
	}
	else
	{
		passprev = temp->prev;
		passnext = temp->next;
		passprev->next = passnext;
	}
}

void	ft_list_middle(t_env *temp)
{
	t_env	*passnext;
	t_env	*passprev;

	passprev = temp->prev;
	passnext = temp->next;
	passprev->next = passnext;
	passnext->prev = passprev;
}

void	ft_unsetsub(char *inputi, t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->field, inputi, strlen(inputi)) == 0)
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	else if (temp->prev == NULL)
		ft_list_start_end(head, temp, true);
	else if (temp->next == NULL)
		ft_list_start_end(head, temp, false);
	else
		ft_list_middle(temp);
	free(temp->field);
	free(temp);
}

void	ft_unset_end_free(t_exec *exec_cmd, t_env **head, t_info **info)
{
	int	a;

	a = 0;
	if ((*info)->inchild == true)
	{
		ft_multifree(head, info, exec_cmd);
		exit(0);
	}
	else
	{
		(*info)->exitstatus = 0;
		while (exec_cmd->argv[a] != NULL)
		{
			free(exec_cmd->argv[a]);
			a++;
		}
		free(exec_cmd);
	}
}

void	ft_unset(t_exec *exec_cmd, t_env **head, t_info **info)
{
	char	**input;
	int		i;

	input = exec_cmd->argv;
	i = 1;
	if (input[i] == NULL)
	{
		(*info)->exitstatus = 0;
		if ((*info)->inchild == true)
		{
			ft_multifree(head, info, exec_cmd);
			exit(0);
		}
	}
	while (input[i] != NULL)
	{
		ft_unsetsub(input[i], head);
		i++;
	}
	ft_unset_end_free(exec_cmd, head, info);
}
