/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:26:35 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/15 17:24:20 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/*#include <stdio.h>
int	main(void)
{	
	printf("%d\n", ft_isalpha('a'));
	printf("%d\n", ft_isalpha(97));
	printf("%d\n", ft_isalpha('B'));
	printf("%d\n", ft_isalpha('0'));
	printf("%d\n", ft_isalpha('@'));
}*/
