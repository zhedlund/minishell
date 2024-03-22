/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:11:00 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/03 17:17:48 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/*#include <stdio.h>
int main(void)
{   
    printf("%d\n", ft_isascii('a'));
    printf("%d\n", ft_isascii(97));
	printf("%d\n", ft_isascii(135));
    printf("%d\n", ft_isascii(-2));
}*/
