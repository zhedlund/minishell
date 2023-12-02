/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:11:56 by zhedlund          #+#    #+#             */
/*   Updated: 2023/12/01 16:01:41 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strpbrk(const char *s1, const char *s2)
{
    int i = 0;

    if (!s1 || !s2)
        return (0);
    while (*s1)
    {
        i = 0;
        while (s2[i])
        {
            if (*s1 == s2[i])
                return ((char *)s1);
            i++;
        }
        s1++;
    }
    return (0);
}

char *ft_strtok(char *str, const char *delim)
{
	static char	*token;
	char		*found;
	char		*result;
	
	if (str != NULL)
		token = str;
	if (token == NULL || *token == '\0')
		return (NULL);
	found = ft_strpbrk(token, delim);
    if (found != NULL)
	{
        *found = '\0';
        found++;
    }
	else
        found = token + ft_strlen(token);
	result = token;
	token = found;
    return (result);
}

/*#include <stdio.h>
int main() {
    char str[] = "This... is ,,a test string.!";
    const char delim[] = " ,.!"; // Delimiters: space, comma, dot, exclamation mark

    char *token = ft_strtok(str, delim);
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = ft_strtok(NULL, delim);
    }
    return 0;
}*/