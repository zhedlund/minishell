/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_relative_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:35:28 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/28 11:35:30 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*ft_namecut(char *totrim)
{
	int		a;
	int		length;
	char	*trimmed;
	int		b;

	b = 0;
	a = 0;
	length = ft_strlen(totrim);
	while (totrim[a] != '=')
		a++;
	a++;
	trimmed = malloc(sizeof(char) * ((length - a) + 1));
	while (totrim[a] != '\0')
	{
		trimmed[b] = totrim[a];
		a++;
		b++;
	}
	trimmed[b] = '\0';
	return (trimmed);
}

char	*ft_findvalue(char *name, t_env **head)
{
	t_env	*temp;
	char	*minusname;
	int		a;
	char	**split;

	a = ft_strlen(name) - 1;
	minusname = NULL;
	temp = *head;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->field, name, a) == 0)
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		return (ft_strdup("\0"));
	split = ft_split(temp->field, '=');
	if (ft_identical(split[0], name) == true)
		minusname = ft_namecut(temp->field);
	ft_freearray(split);
	return (minusname);
}

/*
char	*ft_decidevalue(char *name, t_env **head)
{
	char	*value;
	char	*try;

	if (name[0] >= 48 && name[0] <= 57)
	{
		try = &name[1];
		value = ft_strdup(try);
	}
	else 
		value = ft_findvalue(name, head);
	return (value);
}/*
