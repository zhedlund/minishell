/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:10:42 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/12 12:21:06 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)s;
	while (n != 0)
	{
		new[i] = '\0';
		new++;
		n--;
	}
	s = (void *)new;
}
/*
#include <stdio.h>
int	main(void)
{
	char s[] = "Gleichhhh";
	size_t	b = 3;
	
	ft_bzero(s,b);
	//bzero(s, b);
	//printf("%s", ft_bzero(s, b));
}*/
