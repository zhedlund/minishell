/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:00:46 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/28 11:00:48 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

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

static char	*num_to_array(char *arr, unsigned int number, long int len)
{
	while (number > 0)
	{
		arr[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (arr);
}

static long int	num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		len;
	unsigned int	num;

	len = num_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		num = n * -1;
		str[0] = '-';
	}
	else
		num = n;
	str = num_to_array(str, num, len);
	return (str);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}
