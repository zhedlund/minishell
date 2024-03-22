/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:31:45 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/15 11:15:19 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		i;
	void	*str;
	char	*new;
	int		hold;

	hold = (nmemb * size);
	i = 0;
	str = malloc(sizeof(void) * hold);
	new = (char *)str;
	if (!str)
		return (NULL);
	while (hold != 0)
	{
		new[i] = '\0';
		i++;
		hold--;
	}
	str = (void *)new;
	return (str);
}
/*
#include <stdio.h>
int main(void)
{
	int nmemb = 5;
	int size = 4;
	printf("%p", calloc(nmemb, size));
	printf("\n");
	printf("%p", ft_calloc(nmemb, size));
}*/
