/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:11:56 by zhedlund          #+#    #+#             */
/*   Updated: 2023/12/10 16:00:28 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
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
    const char delim[] = " ,.!"; // Delimiters

    char *token = ft_strtok(str, delim);
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = ft_strtok(NULL, delim);
    }
    return 0;
}*/