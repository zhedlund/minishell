/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:22:47 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/15 18:35:09 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = c;
	if (ch == '\0')
	{
		i = ft_strlen(s);
		return ((char *)s + i++);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int main(void)
{
    char *str = "teste";
    char *res = ft_strchr(str, 'e');
	char *res2 = strchr(str, 'e');
    
    printf("%s\n", res);
	printf("%s\n", res);
   
	return (0);
}*/
