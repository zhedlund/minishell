/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:41:50 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/24 20:34:50 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//count words
static	int	wordcount(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		index;
	int		len;

	index = 0;
	words = malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!words)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			words[index++] = ft_substr(s, 0, len);
			s += len;
		}
		else
		{
			s++;
		}
	}
	words[index] = NULL;
	return (words);
}

/*#include <stdio.h>
int	main(void)

{
	char	*str1 = "**split**this*";

	char	**res = ft_split(str1, '*');
	
	int i = 0;
	while (res[i] != NULL)
	{
		printf("%s\n", res[i]);
		i++;
	}
	free(res);
	return (0);
}*/
