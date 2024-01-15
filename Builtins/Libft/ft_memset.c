/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:32:14 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/16 10:54:17 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	int				i;
	unsigned char	*new;

	i = 0;
	new = (unsigned char *)s;
	while (n != 0)
	{
		new[i] = c;
		i++;
		n--;
	}
	return ((void *)new);
}
/*
#include <stdio.h>
int	main(void)
{
	char s[] = "Gleich";
	int	a = '8';
	size_t	b = 3;
	
	printf("%p\n", memset(s, a, b));
	printf("%p\n", ft_memset(s, a, b));
}*/
