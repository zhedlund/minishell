/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:27:07 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/25 21:35:01 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 	start_ptr: pointer to the first character of the string to be copied
	end_ptr: pointer to the last character of the string to be copied
	return: pointer to the copy of the string
	note: the copy is allocated on the heap and must be freed by the caller */

char	*make_copy(char *start_ptr, char *end_ptr)
{
	size_t	len;
	char	*copy;

	len = end_ptr - start_ptr;
	copy = malloc(len + 1);
	if (copy != NULL)
		ft_strlcpy(copy, start_ptr, len + 1);
	return (copy);
}

int	is_whitespace(const char *buf)
{
	while (*buf != '\0')
	{
		if (!ft_isspace(*buf))
			return (0);
		buf++;
	}
	return (1);
}

bool	ft_identical(char *a, char *b)
{
	if (ft_strlen(a) != ft_strlen(b))
		return (false);
	if (ft_strncmp(a, b, ft_strlen(a)) != 0)
		return (false);
	return (true);
}
