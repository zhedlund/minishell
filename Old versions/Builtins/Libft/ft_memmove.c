/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:22:16 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/16 10:20:27 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)src;
	b = (unsigned char *)dest;
	if (n == 0)
		return (dest);
	if (src == NULL && dest == NULL)
		return (NULL);
	if (b > a)
	{
		while (n--)
			b[n] = a[n];
	}
	if (b < a)
	{
		while (i < n)
		{
			b[i] = a[i];
			i++;
		}
	}
	return ((void *)b);
}
/*#include <stdio.h>
int main (void)
{
	char src[] = "old apple";
	char dest[] = "trawler";
	int n = 4;
	printf("%p", ft_memmove(dest, src, n));
	printf("%p", memmove(dest, src, n)); 
}*/
