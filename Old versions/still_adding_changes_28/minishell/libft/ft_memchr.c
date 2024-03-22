/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:14:23 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/15 17:10:43 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;
	size_t			i;

	str = (unsigned char *)s;
	ch = c;
	i = 0;
	while (i < n)
	{
		if (str[i] == ch)
			return (str + i);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "1212abab";
    char str2[] = "1212abab";
    char cc = '1';
   	char *res = ft_memchr(str, cc, strlen(str));
    char *res2 = memchr(str2, cc, strlen(str));
    
    printf("string from first %c is %s\n", cc, res);
    printf("string from first %c is %s\n", cc, res2);
   
    return (0);
}*/
