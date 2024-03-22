/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:23:06 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/11 12:30:17 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ps;

	ps = (unsigned char *)s;
	while (n != 0)
	{
		*ps = '\0';
		ps++;
		n--;
	}
}

/*#include <stdio.h>
int main()
{
    char buffer[10] = "Hello";

	// Test case 1: Initialize the buffer with non-zero values
   	printf("Before: %s\n", buffer);
    ft_bzero(buffer, sizeof(buffer));
    printf("After: %s\n", buffer);

    // Test case 2: Initialize the buffer with zero values
    ft_memset(buffer, 'A', sizeof(buffer));
    printf("Before: %s\n", buffer);
    ft_bzero(buffer, sizeof(buffer));
    printf("After: %s\n", buffer);

    return (0);
}*/
