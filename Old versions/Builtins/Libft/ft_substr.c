/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:21:36 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/20 20:34:36 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_fill(char const *s, char *s2, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while ((s[i] != '\0') && (i != start))
		i++;
	while (s[i] && (j < len))
	{
		s2[j] = s[i];
		j++;
		i++;
	}
	s2[j] = '\0';
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s2;
	size_t			i;

	i = 0;
	while (s[i])
		i++;
	if (start >= i || *s == '\0')
		return (ft_strdup("", 0));
	if (len > i)
		len = i;
	if (i < start + len)
		len = (i - start);
	s2 = malloc((len + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	else
		ft_fill(s, s2, start, len);
	return (s2);
}
/*int	main(void)
{
	char s[] = "long time ago";
	int	start = 't';
	size_t len = 6;
	printf("%s", ft_substr(s, start, len));
}*/
