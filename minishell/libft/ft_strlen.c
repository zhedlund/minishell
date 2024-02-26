/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:43:50 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/12 16:34:40 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/*#include <stdio.h>
#include <string.h>
int	main (void)
{
	int i;
	int j;
	
	i = ft_strlen("123Abc");
	j = strlen("Abc123");
	printf("%d\n%d\n", i, j);
	return (0);
}*/
