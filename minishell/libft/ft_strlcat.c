/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:33:01 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/11 13:34:25 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dsize;
	size_t	ssize;

	dsize = ft_strlen(dst);
	ssize = ft_strlen(src);
	if (size <= dsize)
		return (size + ssize);
	i = dsize;
	j = 0;
	while ((i + j) < (size - 1) && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dsize + ssize);
}

/*#include <stdio.h>
int	main (void)
{
	char dst[15] = "string1";
	const char src[] = "string2";
	size_t len = ft_strlcat(dst, src, sizeof(dst));

	printf("size: %zu\n", len);
	printf("dst = %s\n", dst);

	return (0);
}
*/
