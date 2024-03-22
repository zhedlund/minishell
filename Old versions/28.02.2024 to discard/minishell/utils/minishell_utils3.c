/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:01:44 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/28 11:01:45 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = c;
	if (ch == '\0')
	{
		i = ft_strlen(s);
		return ((char *)s + i++);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

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

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*join;

	i = 0;
	j = 0;
	if ((*s1 == '\0') && (*s2 == '\0'))
		return (ft_strdup(""));
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
	return (join);
}
