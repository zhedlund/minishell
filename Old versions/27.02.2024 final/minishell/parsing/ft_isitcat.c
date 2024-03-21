/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isitcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:21:41 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/21 15:22:07 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_isitcat(char	*buf, t_info **info)
{
	char **cmdarray;
	int	count;
	int	catcount;
	int	catplus;

	count = 0;
	catcount = 0;
	catplus = 0;
	cmdarray = ft_split(buf, '|');
	while (cmdarray[count] != NULL)
	{
		cmdarray[count] = ft_strtrim(cmdarray[count], " ");
		if (ft_strlen("cat") == ft_strlen(cmdarray[count]) 
			&& ft_strncmp("cat", cmdarray[count], ft_strlen("cat")) == 0)
			catcount++;
		if (ft_strlen(cmdarray[count]) > ft_strlen("cat") &&
			ft_strncmp("cat ", cmdarray[count], ft_strlen("cat ")) == 0)
			catplus++;
		count++;
	}
	if (catplus != 0)
		(*info)->solocat = false;
	if (catcount == 0)
		(*info)->solocat = false;
	if (catcount !=0 && catplus == 0)
		(*info)->solocat = true;
	if (ft_strlen(cmdarray[0]) != ft_strlen("cat") 
		|| ft_strncmp("cat", cmdarray[0], ft_strlen("cat")) != 0)
		(*info)->solocat = false;
	ft_freearray(cmdarray);
}
