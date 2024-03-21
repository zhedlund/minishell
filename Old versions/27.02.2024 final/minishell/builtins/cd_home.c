/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:21:45 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/23 17:21:48 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

bool	ft_homeset(t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->field, "HOME", strlen("HOME")) == 0)
			return (true);
		temp = temp->next;
	}
	return (false);
}

char	*ft_gethome(t_env **head, char *locate)
{
	char	**homeinfo;
	char	*address;
	t_env	*temp;

	temp = (*head);
	homeinfo = NULL;
	address = NULL;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->field, "HOME", strlen("HOME")) == 0)
		{
			homeinfo = ft_split(temp->field, '=');
			if (homeinfo[1] != NULL)
				address = ft_strdup(homeinfo[1]);
			else
			{
				ft_freearray(homeinfo);
				return (locate);
			}
			break ;
		}
		temp = temp->next;
	}
	ft_freearray(homeinfo);
	return (address);
}

char	*ft_home(char *locate, t_env **head, t_info **info)
{
	if (ft_homeset(head) == true)
		locate = ft_gethome(head, locate);
	else
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		(*info)->exitstatus = 1;
		if ((*info)->inchild == true)
			exit(1);
	}
	return (locate);
}
