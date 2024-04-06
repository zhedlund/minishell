/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isitcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:21:41 by zhedlund          #+#    #+#             */
/*   Updated: 2024/04/06 16:28:54 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cat_check(char *cmd)
{
	//char	*hold;

	//hold = ft_strtrim(cmd, " ");
	if (ft_identical(cmd, "cat") == 0)
		return (0);
	if (ft_identical(cmd, "/usr/bin/cat") == 0)
		return (0);
	if (ft_identical(cmd, "/bin/cat") == 0)
		return (0);
	return (9);
}

void	ft_isitcat(char	*buf, t_info **info)
{
	char	**cmdarray;
	int		count;
	int		catcount;
	int		catplus;
	char	*hold;

	count = 0;
	catcount = 0;
	catplus = 0;
	cmdarray = ft_split(buf, '|');
	while (cmdarray[count] != NULL)
	{
		hold = cmdarray[count];
		cmdarray[count] = ft_strtrim(cmdarray[count], " ");
		free(hold);
		if (ft_cat_check(cmdarray[count]) == 0)
			catcount++;
		if (ft_strlen(cmdarray[count]) > ft_strlen("cat")
			&& ft_strncmp("cat ", cmdarray[count], ft_strlen("cat ")) == 0)
			catplus++;
		count++;
	}
	if (catplus != 0)
		(*info)->solocat = false;
	if (catcount == 0)
		(*info)->solocat = false;
	if (catcount != 0 && catplus == 0)
		(*info)->solocat = true;
	if (ft_cat_check(cmdarray[0]) != 0)
		(*info)->solocat = false;
	ft_freearray(cmdarray);
	//ft_freearray(hold);
}
