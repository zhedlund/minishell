/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:20:42 by jelliott          #+#    #+#             */
/*   Updated: 2022/11/30 17:20:46 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <ctype.h>

int	ft_tolower(int c)
{
	if ((c >= 65) && (c <= 90))
		return (c + 32);
	else
		return (c);
}
/*
#include <stdio.h>

int	main (void)
{
	int a = 70;
	int b = 123;
	int c = 83;
	
	printf("%c", ft_tolower(a)); 	
	printf("%c", ft_tolower(b));
	printf("%c", ft_tolower(c));
}*/
