/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:51:57 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/17 20:08:56 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_nsize(int n)
{
	int	nsize;

	nsize = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (10);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		nsize++;
	}
	return (nsize);
}

char	ft_divnsize(int n, int nsize)
{
	if (n == -2147483648 && nsize == 10)
		return ('2');
	if (n == -2147483648 && nsize != 10)
		n = 147483648;
	if (n < 0)
		n *= -1;
	while (nsize != 1)
	{
		n /= 10;
		nsize--;
	}
	n %= 10;
	return (n + '0');
}

char	*ft_itoa(int n)
{
	int		nsize;
	char	*strnew;
	int		a;

	a = 0;
	nsize = ft_nsize(n);
	if (n < 0)
		strnew = malloc((nsize + 2) * sizeof(char));
	if (n >= 0)
		strnew = malloc((nsize + 1) * sizeof(char));
	if (!strnew)
		return (NULL);
	if (n < 0)
	{
		strnew[a] = '-';
		a++;
	}
	while (nsize != 0)
	{
		strnew[a] = ft_divnsize(n, nsize);
		a++;
		nsize -= 1;
	}
	strnew[a] = '\0';
	return (strnew);
}
/*
int    main(void)
{
    int n = -2147483648;
    printf("%s", ft_itoa(n));
}*/
