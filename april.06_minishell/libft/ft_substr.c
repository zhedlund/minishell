/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:05:45 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/18 14:36:53 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	char			*src;
	size_t			sublen;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	src = (char *)s + start;
	if (ft_strlen(src) < len)
		sublen = ft_strlen(src) + 1;
	else
		sublen = len + 1;
	sub = malloc(sublen * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, src, sublen);
	return (sub);
}

/*#include <stdio.h>
int	main(void)
{
	const char	*str1 = "##### I only want this part #############";
	char	*str2 = ft_substr(str1, 6, 22);
	
	printf("Substring: %s\n", str2);
	free(str2);
	return (0);
}*/
