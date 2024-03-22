/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocchecks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:23:57 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/06 17:24:00 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Builtins.h"
#include "../Libft/libft.h"
#include <sys/ioctl.h>

bool	ft_validheredoc(int heredoc, char *file)
{
	bool	valid;

	valid = false;
	if (heredoc == 0 && file == NULL || file[0] == '<' || file[0] == '>' 
		|| file[0] == '\0' || file[0] == '\n' || file[0] == '|')
	{
		printf("minishell: syntax error near '<<'\n");
		return (true);
	}
	return (false);
}

void	ft_hdcount(char **temp, t_info **info)
{
	int	i;
	
	i = 0;
	while (temp[i] != NULL)
	{
		if (ft_strncmp(temp[i], "<<", 2) == 0)
		{
			(*info)->panic = ft_validheredoc((*info)->hdcount, temp[i + 1]);
			(*info)->hdcount++;
			if (i != 0 && (*info)->hdcount >= 1 && ft_strncmp(temp[i - 1], "cat", 2) == 0)
				(*info)->catcount++;
		}
		i++;
	}
	if ((*info)->panic == true)
	{
		if (temp)
			ft_freearray(temp);
	}
}

char	**ft_checkheredoc(char **inputs, t_info **info)
{
	char	**heredocarray;
	char	**temp;
	char	*pass;

	(*info)->panic = false;
	temp = ft_split(inputs[0], ' ');
	ft_hdcount(temp, info);
	if ((*info)->panic == true)
	{
		ft_freearray((*info)->inputs);
		return (NULL);
	}
	if ((*info)->hdcount == 0)
	{
		ft_freearray(temp);
		return (inputs);
	}
	heredocarray = ft_heredocarray((*info)->hdcount, temp); //extract from inputs
	ft_heredocexecute(heredocarray, info); //while loop - see notes
	pass = ft_newinputsarray(temp, info);
	if (temp)
		ft_freearray(temp);
	if (!pass)
	{
		ft_freearray((*info)->inputs);
		return (NULL);
	}
	temp = ft_split(pass, ';');
	free(pass);
	ft_freearray((*info)->inputs); //is this helping?
	return(temp);
}
