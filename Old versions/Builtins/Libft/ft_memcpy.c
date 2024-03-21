/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:41:29 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/15 19:15:31 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int		i;
	int		j;
	char	*newdest;
	char	*newsrc;

	i = 0;
	j = 0;
	newdest = (char *)dest;
	newsrc = (char *)src;
	if (n == 0 || src == dest)
		return (dest);
	if (src == NULL && dest == NULL)
		return (NULL);
	while (n != 0)
	{
		newdest[i] = newsrc[j];
		n--;
		i++;
		j++;
	}
	dest = (void *)newdest;
	return (dest);
}
/*
#include <stdio.h>
int main(void)
{
	char dest[] = "slipper";
	char src[] = "sh";
	int a = 2;
	printf("%p", ft_memcpy(dest, src, a));
	printf("%p", memcpy(dest, src, a));
}*/
