/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:54:19 by zhedlund          #+#    #+#             */
/*   Updated: 2023/12/02 16:59:47 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/*#include <stdio.h>
#include <string.h>
int	main (void)
{
	printf("%d\n", ft_strcmp("abcde", "Abcde"));
	printf("%d\n", strcmp("abcde", "Abcde"));
	return (0);
}*/