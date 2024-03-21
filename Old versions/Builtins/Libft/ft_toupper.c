/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:57:44 by jelliott          #+#    #+#             */
/*   Updated: 2022/11/30 16:57:51 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <ctype.h>

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}
/*
#include <stdio.h>

int	main (void)
{
	int a = 98;
	int b = 123;
	int c = 100;
	
	printf("%c", ft_toupper(a)); 	
	printf("%c", ft_toupper(b));
	printf("%c", ft_toupper(c));
}*/
