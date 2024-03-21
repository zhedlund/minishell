/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:36:37 by jelliott          #+#    #+#             */
/*   Updated: 2022/11/30 11:36:43 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (size <= 0)
		return (j);
	while (size != 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	dst[i] = '\0';
	return (j);
}
/*
#include <stdio.h>

int	main(void)
{
	char dst[10] = "Gravity";
	char src[9] = "stole";
	int a = 3;
	
	printf("%s", ft_strlcpy(dst, src, a));
}*/
