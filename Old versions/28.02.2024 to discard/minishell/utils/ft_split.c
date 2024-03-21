/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:26:24 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/19 23:04:45 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

//finding number of strings
int	ft_deliminator(char const *s, char c)
{
	int			i;
	int			a;
	int			j;
	char const	*t;

	i = 0;
	a = 1;
	t = s;
	j = 0;
	while (s[i] == c && s[i] != '\0')
	{
		s++;
		t++;
	}
	while (t[j] != '\0')
	{
		t++;
		if (t[j] == '\0')
			return (a);
		if ((s[i] == c) && (t[j] != c))
			a += 1;
		s++;
	}
	return (a);
}

//returning pointer to populated n string
char	*ft_swap(char const *s, char c, int len)
{
	char	*ptr;
	int		i;

	len = 0;
	i = 0;
	while (s[i] == c && s[i] != '\0')
		s++;
	while (s[i] != c && s[i] != '\0')
	{
		s++;
		len++;
	}
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (0);
	s -= (len);
	len = 0;
	while ((s[i] != c) && (s[i] != '\0'))
	{
		ptr[len] = s[i];
		len++;
		s++;
	}
	ptr[len] = '\0';
	return (ptr);
}

///move to the correct bit of the original string
char const	*ft_place(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		s++;
	while (s[i] != c && s[i] != '\0')
		s++;
	return (s);
}

int	ft_same(char const *s, char c)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (s[i] != '\0')
		i++;
	while (s[a] == c)
		a++;
	if (a == i)
		return (-1);
	else
		return (3);
}

char	**ft_split(char const *s, char c)
{
	int		a;
	int		i;
	char	**ptr;

	i = 0;
	if (*s == '\0' || (ft_same(s, c) == -1))
		a = 0;
	else
		a = ft_deliminator(s, c);
	ptr = (char **)malloc((a + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	while (a != 0)
	{
		ptr[i] = ft_swap(s, c, i);
		s = ft_place(s, c);
		i++;
		a--;
	}
	ptr[i] = NULL;
	return (ptr);
}
/*
#include <stdio.h>

int main(void)
{
    char s[] = "hello!";
    char c = ' ';

    printf("%p", ft_split(s, c));
}*/
