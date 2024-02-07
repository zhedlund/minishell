/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:08:27 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/15 19:10:39 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	int				j;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	j = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n != 1 && a[i] == b[j])
	{
		i++;
		j++;
		n--;
	}	
	return (a[i] - b[j]);
}
/*
#include <stdio.h>
int main(void)
{
	char s1[] = "traum";
	char s2[] = "traum";
	int n = 5;
	
	printf("%d", ft_memcmp(s1, s2, n));
	printf("%d", memcmp(s1,s2,n));
}*/
