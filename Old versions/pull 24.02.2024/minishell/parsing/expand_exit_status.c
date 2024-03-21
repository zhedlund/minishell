/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:23:46 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/23 17:30:56 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

void	error_max_size(void)
{
	ft_putstr_fd("Expanded string exceeds maximum size\n", 2);
	exit(EXIT_FAILURE);
}

void	expand_exit_status(int exit_status, char *expanded, size_t *index)
{
	char	*exit_str;
	size_t	len;
	size_t	remaining_str;

	exit_str = ft_itoa(exit_status);
	len = ft_strlen(exit_str);
	if (*index + len >= PATH_MAX)
	{
		free(exit_str);
		error_max_size();
	}
	remaining_str = PATH_MAX - *index;
	ft_strlcpy(expanded + *index, exit_str, remaining_str);
	*index += len;
	free(exit_str);
}
