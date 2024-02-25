/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:03:02 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/15 17:23:36 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

/*#include <stdio.h>
int main(void)
{   
    printf("%d\n", ft_isalnum('a'));
    printf("%d\n", ft_isalnum('9'));
    printf("%d\n", ft_isalnum(9));
	printf("%d\n", ft_isalnum('!'));
}*/
