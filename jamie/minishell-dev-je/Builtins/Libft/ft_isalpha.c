/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftisalpha.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:52:40 by jelliott          #+#    #+#             */
/*   Updated: 2022/11/28 13:54:13 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>

int	main (void)
{
	char a = 'A';
	char b = 'b';
	int c = 25;
	
	printf("%c", ft_isalpha(a));
	printf("%c", ft_isalpha(b));
	printf("%c", ft_isalpha(c));
}*/
