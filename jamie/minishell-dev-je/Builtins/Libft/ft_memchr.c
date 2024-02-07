/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:44:36 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/15 19:24:14 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	int		i;
	char	*a;
	char	b;

	i = 0;
	a = (char *)s;
	b = (char)c;
	if (n <= 0)
		return (NULL);
	while (n != 1 && a[i] != b)
	{
		a++;
		n--;
	}
	if (a[i] != (char)c)
		return (NULL);
	return ((void *) a);
}
/*
#include <stdio.h>
int main(void)
{
	char s[] = "/|\x12\xff\x09\x42\2002\42|\\";
	int c = '\200';
	int n = 10;
	
	printf("%p", ft_memchr(s,c,n));
	printf("%p", memchr(s,c,n));
}*/
