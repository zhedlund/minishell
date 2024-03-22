/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:45:12 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/17 10:45:15 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

int	ft_end(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_end(s);
	if (s[i] == (c % 256))
		return ((char *)s + i);
	while (i != 0 && s[i] != (c % 256))
		i--;
	if (s[i] == (c % 256))
		return ((char *)s + i);
	else
		return (NULL);
}
/*
#include <stdio.h>

int main (void)
{
	char s[] = "penultimaate";
	int c = 'a';
	printf("%s", ft_strrchr(s, c));
}*/
