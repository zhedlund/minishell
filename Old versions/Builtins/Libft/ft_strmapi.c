/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:49:58 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/16 20:24:26 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>

int	ft_length(char const *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new;
	unsigned int	i;

	i = 0;
	new = malloc(sizeof(char) * ft_length(s) + 1);
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	ft_map(unsigned int i, char letter)
{
	letter = letter + 5;
	i++;
	return (letter);
}
/*
int main (void)
{
	char *s = "String";
	char (*f)(unsigned int, char);
	f = &ft_map;
	printf("New String is %s", ft_strmapi(s, f));
}*/
