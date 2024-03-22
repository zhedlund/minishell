/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:54:22 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/26 11:54:41 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	str = ft_strdup(s);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*#include <stdio.h>
char	ctoupper(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z')
        	return (c - 32);
	return (c);
}

int main(void)
{
	char s1[] = "abcdefg";
    	char *result1 = ft_strmapi(s1, ctoupper);
    
	if (result1 == NULL)
		printf("Memory allocation failed for test case 1\n");
        // Handle the error case
    else
    {
        printf("Result: %s\n", result1);
        // Verify the result
        free(result1); // Free the allocated memory
    }
	return (0);
}*/
