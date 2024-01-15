/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:48:51 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/04 16:48:54 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Builtins.h"

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
