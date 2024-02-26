/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:48:41 by zhedlund          #+#    #+#             */
/*   Updated: 2023/05/03 16:59:23 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_isdigit('0'));
	printf("%d\n", ft_isdigit(48));
	printf("%d\n", ft_isdigit('a'));
	printf("%d\n", ft_isdigit(97));
}*/
