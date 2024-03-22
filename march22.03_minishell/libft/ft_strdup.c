/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:01:13 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/16 19:51:40 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s) + 1;
	s2 = malloc(len * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s, len);
	return (s2);
}

/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char *str = "here we go";
	char	*dup = ft_strdup(str);
	char	*comp = strdup(str);

	if (dup && comp)
	{
		printf("Original string: %s\n", str);
		printf("Duplicated string: %s\n", dup);
		printf("strdup: %s\n", comp);
		
		free(dup);
		free(comp);
	}
	else
		printf("Memory allocation failed\n");
	
	return (0);
}*/
