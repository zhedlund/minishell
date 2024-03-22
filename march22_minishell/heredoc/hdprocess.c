/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdprocess.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:50:12 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/25 21:33:56 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_hdctrld(char *input, t_info **info, char *hdarray)
{
	if (input == NULL && ((*info)->runhere < (*info)->hdcount - 1))
	{
		printf("unexpected heredoc delineation,");
		printf("expecting: %s\n", hdarray);
	}
	(*info)->runhere++;
}

void	ft_hdprocess(char **hdarray, t_info **info, int fd, char *input)
{
	int	i;

	i = 0;
	while (g_signal == 0 && (*info)->runhere != (*info)->hdcount)
	{
		input = (readline("heredoc<< "));
		if (input != NULL 
			&& ft_identical(hdarray[i], input) == false)
			write(fd, input, ft_strlen(input));
		if (input == NULL || (ft_strlen(hdarray[i]) == ft_strlen(input) 
				&& ft_strncmp(hdarray[i], input, ft_strlen(hdarray[i])) == 0))
		{
			ft_hdctrld(input, info, hdarray[i]);
			i++;
		}
		free (input);
		if ((*info)->runhere == (*info)->hdcount)
			break ;
		write(fd, "\n", 1);
	}
}
