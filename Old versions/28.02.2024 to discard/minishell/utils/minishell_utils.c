/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:27:07 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/23 22:17:22 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

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

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	nl;

	nl = '\n';
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
	write(fd, &nl, 1);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ps;
	char	uc;

	ps = (char *)s;
	uc = (char)c;
	while (n > 0)
	{
		ps[n - 1] = uc;
		n--;
	}
	return (ps);
}
