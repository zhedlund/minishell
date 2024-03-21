/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:25:22 by jelliott          #+#    #+#             */
/*   Updated: 2022/11/30 17:25:27 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (c % 256) && s[i] != '\0')
		s++;
	if (s[i] == (c % 256))
		return ((char *)s);
	else
		return (NULL);
}
/*
#include <stdio.h>

int main (void)
{
	char s[] = "teste";
	int	c = '\0';
	char *p;
	p = ft_strchr(s, c);
	//printf("%s", "Error");
	if(!p)
		return(printf("%s", "Error"));
	//printf("%s\n", p);
	printf("%c", *strchr(s,c));
}*/
