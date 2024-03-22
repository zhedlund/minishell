/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 20:04:28 by jelliott          #+#    #+#             */
/*   Updated: 2022/12/02 20:04:34 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int	minus;
	int	i;
	int	b;

	b = 0;
	minus = 1;
	i = 0;
	while (nptr[b] == ' ' || (nptr[b] >= 9 && nptr[b] <= 13))
		nptr++;
	if (nptr[b] == '-')
		minus *= -1;
	if (nptr[b] == '+' || nptr[b] == '-')
		nptr++;
	if (nptr[b] < '0' || nptr[b] > '9')
		return (0);
	while (nptr[b] == '0')
		nptr++;
	while (nptr[b] >= '0' && nptr[b] <= '9')
	{
		i = (nptr[b] - '0') + i * 10;
		b++;
	}
	return (i * minus);
}
/*
int	main(void)
{
	char *str = "+-1234ab567";
	int end = ft_atoi(str);
    printf("%d", end);
    //printf("\n");
    //printf("%d", atoi(str));
}*/
