/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:24:21 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:24:23 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Builtins.h"
#include <errno.h>
# include "Libft/libft.h"
#include <limits.h>
//using errno to print the error message, but need to check if we are allowed to use this
//problem here that there is no variable to give - same with some other builtin functions
//this function uses getcwd to store the pwd in a string and then prints the string
int    ft_pwd(char *arraystring)
{
	char	store[PATH_MAX];
	char	*path;
	int	i;
	int	fd[2];
	
	i = 0;
	path = getcwd(store, sizeof(store));
	if (path)
	{
		while (path[i] != '\0')
		{
			write(1, &path[i], 1);
			i++;
		}
	}
	else
		printf("%s", strerror(errno));
	write(1, "\n", 1);
	return (0);
}

