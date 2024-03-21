/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:22:47 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:22:49 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "Builtins.h"
# include "Libft/libft.h"

//the very basic execution of the echo command
//I don't think argv will work as there might be complex commands like cd /home | ls > file.txt
//even echo could be added at the end e.g.cd /home | ls > file.txt | echo "pipes"
//what to do instead? - use ft_split to make the command line into an array using ' ' (unless there is some situation where this wouldn't work? we want the commands and the pipes in the array seperately)
int    ft_echo(char *arraystring)
{
	int	i;
	int	newline;
	
	i = 5;
	newline = 3;
	if (ft_strlen(arraystring) >= 7) 
		newline = ft_strncmp(arraystring, "echo -n", 7);
	if (newline == 0)
		i = 8;
	if (ft_strlen(arraystring) == 4)
		write (1, &arraystring[4], 1);
	else
	{
		while (arraystring[i] != '\0')
		{
			write (1, &arraystring[i], 1);
			i++;
		}
	}
	if (newline != 0)
		write(1, "\n", 1);
	return (0);
}
