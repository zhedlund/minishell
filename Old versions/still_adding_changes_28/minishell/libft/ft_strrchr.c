/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:20:46 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/15 18:39:00 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = c;
	i = ft_strlen(s);
	if (ch == '\0')
		return ((char *)s + i++);
	while (i >= 0)
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int main(void)
{
    char *str = "teste";
    char *res = ft_strrchr(str, 'e');
	char *res2 = strrchr(str, 'e');
    
    printf("%s\n", res);
	printf("%s\n", res2);
   
	return (0);
}*/
