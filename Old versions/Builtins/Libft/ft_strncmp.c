/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:54:18 by jelliott          #+#    #+#             */
/*   Updated: 2022/12/02 17:54:24 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (--n && (s1[i] == s2[i]) && (s1[i] != '\0') && (s2[i] != '\0'))
		i++;
	if ((unsigned char)s1[i] > (unsigned char)s2[i])
		return (1);
	if ((unsigned char)s1[i] < (unsigned char)s2[i])
		return (-1);
	else
		return (0);
}
/*
#include <stdio.h>

int main (void)
{
	//char a[] = "sZZZZZ"; 
	//char b[] = "svdjg70977b";
	//int n = 5;
	
	//printf("%d", ft_strncmp(a, b, n));
	ft_strncmp("abcdefgh", "abcdwxyz", 4);
}*/
