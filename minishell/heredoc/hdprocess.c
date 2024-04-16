/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdprocess.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:50:12 by jelliott          #+#    #+#             */
/*   Updated: 2024/04/06 16:27:15 by zhedlund         ###   ########.fr       */
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

void	ft_hdprocess(char **hdarray, t_info **info, int fd, t_env **head)
{
	int		i;
	char	*hold;

	i = 0;
	while (g_signal == 0 && (*info)->runhere != (*info)->hdcount)
	{
		(*info)->hdinput = (readline("> "));
		if ((*info)->hdinput != NULL 
			&& ft_identical(hdarray[i], (*info)->hdinput) == false)
		{
			hold = expand_env_in_str((*info)->hdinput, 0, head);
			write(fd, hold, ft_strlen(hold));
			free(hold);
		}
		if ((*info)->hdinput == NULL 
			|| (ft_identical(hdarray[i], (*info)->hdinput) == 1))
		{
			ft_hdctrld((*info)->hdinput, info, hdarray[i]);
			i++;
		}
		free ((*info)->hdinput);
		if ((*info)->runhere == (*info)->hdcount)
			break ;
		write(fd, "\n", 1);
	}
}
