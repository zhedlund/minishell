/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:54:41 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/15 19:48:02 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	char		*s;

	d = (char *)dest;
	s = (char *)src;
	if (n == 0 || d == s)
		return (dest);
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

int main() {
    char source[] = "123456";
    char destination[20];

	 // Copy the contents of source to destination
    ft_memcpy(destination, source, strlen(source) + 1);

    // Verify the copy
    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    // Compare the original source and the destination
    if (strcmp(source, destination) == 0) {
        printf("Memcpy successful.\n");
    } else {
        printf("Memcpy failed.\n");
    }

	//compare with original function
	char source2[] = "123456";
    char destination2[20];

    memcpy(destination, source, strlen(source) + 1);
    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);
    if (strcmp(source, destination) == 0) {
        printf("Memcpy successful.\n");
    } else {
        printf("Memcpy failed.\n");
    }

    return 0;
}*/
