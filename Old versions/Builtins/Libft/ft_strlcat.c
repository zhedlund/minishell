/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:14:13 by jelliott          #+#    #+#             */
/*   Updated: 2022/11/30 12:18:20 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

size_t	ft_length2(const char *src)
{
	size_t	a;

	a = 0;
	while (src[a] != '\0')
	{
		a++;
	}
	return (a);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	a;

	a = ft_length2(src);
	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (src[j] && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + a);
}
/*
#include <stdio.h>

int	main(void)
{
	char dst[15] = "groan";
	char src[5] = "alone";
	int	a = 5;
	
	printf("%ld", ft_strlcat(dst, src, a));
	printf("/n");
	printf("%ld", strlcat(dst, src, a));
}*/
