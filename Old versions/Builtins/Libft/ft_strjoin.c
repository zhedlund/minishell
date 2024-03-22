/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:04:59 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/17 12:22:41 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_mallocjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*join;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	join = malloc((i + j + 1) * sizeof(char));
	if (!join)
		return (0);
	return (join);
}

char	*ft_strjoin(char const *s1, char const *s2, int tofree)
{
	unsigned int	i;
	unsigned int	j;
	char			*join;

	i = 0;
	j = 0;
	if ((*s1 == '\0') && (*s2 == '\0'))
		return (ft_strdup("", 0));
	join = ft_mallocjoin(s1, s2);
	if (!join)
		return (0);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	if (tofree == 0 || tofree == 2)
		free((void *)s1);
	if (tofree == 0 || tofree == 3)
		free((void *)s2);
	return (join);
}
/*
int	main(void)
{
	char s1[] = "";
	char s2[] = "";
	//char *s3 = "the nyancat";
	//printf("%s", ft_strjoin(ft_strjoin(s1, s2), s3));
	printf("%s", ft_strjoin(s1, s2));
}*/
