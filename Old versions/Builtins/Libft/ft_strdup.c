/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:35:09 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/20 16:08:42 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char	*ft_strdup(const char *s, int rid)
{
	int		i;
	char	*sdup;

	i = 0;
	if (*s != '\0')
	{
		while (s[i])
			i++;
		sdup = malloc((i + 1) * sizeof(char));
		if (!sdup)
			return (0);
		i = 0;
		while (s[i])
		{
			sdup[i] = s[i];
			i++;
		}
	}
	else
		sdup = malloc((i + 1) * sizeof(char));
	if (!sdup)
		return (0);
	sdup[i] = '\0';
	if (rid == 1 && s)
		free((void *)s);
	return (sdup);
}
/*
int	main(void)
{
	char s[] = "long time ago";
	
	printf("%s", ft_strdup(s));
}*/
