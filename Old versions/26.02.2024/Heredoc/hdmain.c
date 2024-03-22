/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdmain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:18:05 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/20 10:18:07 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

bool	ft_validheredoc(int heredoc, char *file)
{
	bool	valid;

	valid = false;
	//printf("file == %s\n", file);
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
		(*info)->hdcount = 0;
		(*info)->catcount = 0;
	}
}

char	**ft_checkheredoc(char **inputs, t_info **info)
{
	char	**heredocarray;
	char	**temp;
	//char	*pass;

	(*info)->panic = false;
	temp = ft_split(inputs[0], ' ');
	ft_hdcount(temp, info);
	if ((*info)->panic == true)
		return (NULL);
	if ((*info)->hdcount == 0)
	{
		ft_freearray(temp);
		return (inputs);
	}
	(*info)->first = true;
	heredocarray = ft_heredocarray((*info)->hdcount, temp); //extract from inputs
	ft_heredocexecute(heredocarray, info); //while loop - see notes
	ft_freearray(temp); //is this helping?
	return(NULL);
}

void	ft_heredocmain(char *cmdline, t_info **info)
{
	int	i;
	
	i = 0;
	(*info)->inputs = ft_split(cmdline, ';');
	while ((*info)->inputs[i] != NULL)
	{
		if ((*info)->inputs[i] == NULL)
			break ;
		(*info)->inputs[i] = ft_strtrim((*info)->inputs[i], " ");
		ft_checkheredoc((*info)->inputs, info);
		i++;
	}
	ft_freearray((*info)->inputs);
}
