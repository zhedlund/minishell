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
#include "Builtins.h"
# include "Libft/libft.h"
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
int   ft_env(char *arraystring)
{
	int	i;
	extern char	**environ;
	int	j;
	
	i = 3;
	j = 0;
	if (arraystring[i] != '\0')
		return(ft_envsub(i, j, arraystring));
	else
	{
		while (environ[j] != NULL)
		{
			printf("%s\n", environ[j]);
			j++;
		}
	}
	return (0);
}
