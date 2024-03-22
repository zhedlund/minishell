/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isprint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:21:20 by jelliott          #+#    #+#             */
/*   Updated: 2022/11/29 12:21:29 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>

int main (void)
{
	int a = 0;
	int b = 1;
	int c = 49;
	
	printf("%c", ft_isprint(a));
	printf("%c", ft_isprint(b));
	printf("%c", ft_isprint(c));
}*/		
