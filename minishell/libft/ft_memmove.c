/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:28:29 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/11 16:20:43 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	if (dest == src)
		return (dest);
	if (s < d)
		while (n--)
			*(d + n) = *(s + n);
	else
		while (n--)
			*d++ = *s++;
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

void *ft_memmove(void *dest, const void *src, size_t n);

int main(void) 
{
    char str[] = "1234 abcd";
	char str2[] = "1234 abcd";

	printf("Before: %s\n", str);
    ft_memmove(str + 5, str, 4);
    printf("After: %s\n", str);

    // to compare
	printf("Before: %s\n", str2);
    memmove(str2 + 5, str2, 4);
    printf("After: %s\n", str2);

    return (0);
}*/
