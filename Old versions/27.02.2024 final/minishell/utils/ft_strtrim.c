/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:23:30 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/19 23:21:05 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*ft_straightcopy(char const *s1, int i)
{
	char	*trimmedbck;

	while (s1[i] != '\0')
		i++;
	trimmedbck = malloc((i + 1) * sizeof(char));
	if (!trimmedbck)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		trimmedbck[i] = s1[i];
		i++;
	}
	trimmedbck[i] = '\0';
	return (trimmedbck);
}

int	ft_measure(char const *hold, char const *set)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	j = 0;
	i = 0;
	while (hold[len] != '\0')
		len++;
	while (hold[i] != '\0')
	{
		while (set[j] != '\0')
		{
			if (hold[i] == set[j])
				break ;
			j++;
		}
		if (hold[i] != set[j])
			break ;
		i++;
		j = 0;
	}
	if (len == i)
		return (-1);
	return (i);
}

char	*ft_trimmed(const char *s1, int i, int j)
{
	int		a;
	int		b;
	char	*trimmedbck;

	a = 0;
	b = 0;
	while (s1[a] != '\0')
		a++;
	trimmedbck = malloc(((a - (i + j)) + 1) * sizeof(char));
	if (!trimmedbck)
		return (0);
	while (i != (a - j))
	{
		trimmedbck[b] = s1[i];
		i++;
		b++;
	}
	trimmedbck[b] = '\0';
	return (trimmedbck);
}

char	*ft_bck(const char *s1, int i)
{
	char	*bck;
	int		j;

	j = 0;
	while (s1[i] != '\0')
		i++;
	bck = malloc((i + 1) * sizeof(char));
	if (!bck)
		return (0);
	i -= 1;
	while (i >= 0)
	{
		bck[j] = s1[i];
		i--;
		j++;
	}
	bck[j] = '\0';
	return (bck);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*trimmedbck;

	i = 0;
	j = 0;
	if (*set == '\0' && *s1 != '\0')
	{
		trimmedbck = ft_straightcopy(s1, i);
		if (!trimmedbck)
			return (0);
		return (trimmedbck);
	}
	trimmedbck = ft_bck(s1, i);
	if (!trimmedbck)
		return (0);
	i = ft_measure(s1, set);
	j = ft_measure (trimmedbck, set);
	free(trimmedbck);
	if ((*s1 == '\0') || (i == -1))
		return (ft_strdup(""));
	trimmedbck = ft_trimmed(s1, i, j);
	free((void *)s1);
	return (trimmedbck);
}
/*
int main(void)
{
    char s1[] = "";
    char set[] = "";
    printf("%s", ft_strtrim(s1, set));
}

//empty strings - s1 return empty ; set return copy of s1
//single characters
//none on one side*/
