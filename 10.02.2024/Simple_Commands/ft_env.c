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
//this function deals with a specified env variable
int	ft_envsub(int i, int j, char *arraystring)
{
	char	*variable;
	
	i++;
	while (arraystring[i] != '\0')
		i++;
	variable = malloc(sizeof(char) * (i + 1));		
	if (!variable)
		return (1);
	i = 4;
	while (arraystring[i] != '\0')
	{
		variable[j] = arraystring[i];
		j++;
		i++;
	}
	variable[j] = '\0';
	printf("%s\n", getenv(variable));
	free (variable);
	return (0);
}

//env might be used alone - prints the entire environment
//or with a specified variable, in which case want to print info pertaining to that
//this function primarily deals with env being used alone
void   ft_env(char *arraystring, t_env **head)
{
	int	i;
	//extern char	**environ;
	int	j;
	t_env	*temp;
	
	temp = *head;
	i = 3;
	j = 0;
	//if (arraystring[i] != '\0')
	//	return(ft_envsub(i, j, arraystring));
	//else
	//{
		while (temp != NULL)
		{
			printf("%s\n", temp->field);
			temp = temp->next;
		}
	//}
}