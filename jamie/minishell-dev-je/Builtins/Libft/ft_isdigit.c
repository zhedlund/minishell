/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:21:01 by jelliott          #+#    #+#             */
/*   Updated: 2022/11/28 16:21:15 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	else
		return (1);
}
/*
#include <stdio.h>
int	main (void)
{
	char a = 'A';
	char b = 'b';
	int c = 57;
	
	printf("%c", ft_isdigit(a));
	printf("%c", ft_isdigit(b));
	printf("%c", ft_isdigit(c));
}*/
