/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:23:06 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/26 11:56:02 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/*#include <stdio.h>
#include <limits.h>
int main(void)
{
    int number = -2147483647LL;
    char *res = ft_itoa(number);
    printf("Integer: %d\nString: %s\n", number, res);
    free(res);
    printf("%s", res);

    return (0);
}*/
