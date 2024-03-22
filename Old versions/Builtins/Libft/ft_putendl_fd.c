/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:06:36 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/16 11:43:35 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	nl;

	nl = '\n';
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
	write(fd, &nl, 1);
}
/*
int main (void)
{
 char s[] = "drum roll";
 int fd = 1;
 ft_putendl_fd(s,fd);
}*/
