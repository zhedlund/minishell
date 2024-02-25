/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:37:58 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/24 20:14:02 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*newstr;

	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	newstr = malloc(sizeof(char) * len);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, len);
	ft_strlcat(newstr, s2, len);
	return (newstr);
}

/*char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = malloc(sizeof(char) * len);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}*/

/*#include <stdio.h>
int	main(void)
{
	char	*str1 = "123";
	char	*str2 = "abc";
	char	*str3 = "!!!";
	char	*tmp = ft_strjoin(str1, str2);
	char 	*res = ft_strjoin(tmp, str3);
	
	printf("%s\n", tmp);
	free(tmp);
	printf("%s\n", tmp);
	printf("%s\n", res);
	free(res);
	return (0);
}*/
