/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:24:47 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/16 14:39:45 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

char	ft_div(int n, int length)
{
	int		div;
	char	a;

	div = 1;
	while (length != 1)
	{
		div *= 10;
		length--;
	}
	n /= div;
	n %= 10;
	a = (n + '0');
	return (a);
}

int	ft_length1(int n)
{
	int	length;

	length = 1;
	while (n > 9)
	{
		n /= 10;
		length++;
	}
	return (length);
}

void	ft_min(int fd)
{
	write(fd, "-2147483648", 11);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		length;

	c = 'a';
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		length = ft_length1(n);
		while (length != 0)
		{
			c = ft_div(n, length);
			length--;
			write(fd, &c, 1);
		}
	}
}
/*
int main(void)
{
	int fd = 2;
	int n = -2147483648;
	ft_putnbr_fd(n, fd);
}*/
