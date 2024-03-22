/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:01:15 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/16 17:13:18 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while ((i + j < len) && (big[i + j] == little[j]) && little[j] != '\0')
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <bsd/string.h> //compile with flag -lbsd
int	main(void)
{
	const char *str = "string to search";
	const char *lstr = "to";
	char	*ptr;
	char	*comp;

	ptr = ft_strnstr(str, lstr, 17);
	comp = strnstr(str, lstr, 17);
	printf("%s\n", ptr);
	printf("%s\n", comp);
	
	return (0);
}*/
