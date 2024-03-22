/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:20:06 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/16 18:59:02 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/*#include <stdio.h>
#include <stdlib.h>
int	main(void)
{
	size_t elements = 5;
	size_t element_size = sizeof(int);
	int	*arr = ft_calloc(elements, element_size);

	if (arr == NULL) {
		printf("Allocation failed.\n");
	return (1);
	}    
    // Verify the allocated memory is initialized to zero
    for (size_t i = 0; i < elements; i++) {
        if (arr[i] != 0) {
            printf("Memory not initialized to zero.\n");
		free(arr);
		return (1);
		}
	}
    // Success
    printf("Memory allocation and initialization succeeded.\n");
	free(arr);
    return 0;
}*/
