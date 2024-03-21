/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:18:35 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/17 00:53:56 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

int	ft_compare(const char *big, const char *little, size_t len, size_t i)
{
	int		a;
	size_t	j;

	a = 5;
	j = 0;
	while ((i < len) && (big[i] != '\0') && (big[i] == little[j]))
	{
		i++;
		j++;
	}
	if (little[j] == '\0')
		a = 1;
	else
		a = 0;
	return (a);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	int		a;

	i = 0;
	a = 0;
	j = 0;
	if (*little == '\0')
		return (((char *)big));
	while ((big[i]) && (i < len))
	{
		if (big[i] == little[j])
			a = ft_compare(big, little, len, i);
		if (a == 1)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main (void)
{
	char big[] = "Passsowrd";
	char little[] = "wrd";
	size_t len = -1;
	
	printf("%s", ft_strnstr(big, little, len));
}*/
