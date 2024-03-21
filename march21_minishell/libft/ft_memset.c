/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:28:46 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/11 13:51:00 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ps;
	char	uc;

	ps = (char *)s;
	uc = (char)c;
	while (n > 0)
	{
		ps[n - 1] = uc;
		n--;
	}
	return (ps);
}
/*#include <stdio.h>
int main()
{
    char str[6] = "Hello";
    
    printf("Before: %s\n", str);
    ft_memset(str, '*', 6);
    printf("After: %s\n", str);
	
	return (0);
}*/
