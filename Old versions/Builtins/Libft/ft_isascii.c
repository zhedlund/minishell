/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isascii.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:13:11 by jelliott          #+#    #+#             */
/*   Updated: 2022/11/29 12:13:21 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

int	ft_isascii(int c)
{
	if (c < 0 || c > 127)
		return (0);
	else
		return (1);
}
/*
#include <stdio.h>
int main (void)
{
	char a = '@';
	char b = 156;
	int c = 50;
	
	printf("%c", ft_isascii(a));
	printf("%c", ft_isascii(b));
	printf("%c", ft_isascii(c));
}*/
