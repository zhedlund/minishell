/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdmain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:18:05 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/22 11:52:58 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

bool	ft_validheredoc(t_info **info, bool direct, int heredoc, char *file)
{
	bool	valid;
	int	a;

	valid = false;
	a = 0;
	(*info)->nospace = direct; // error: no member named 'nospace' in 'struct s_info', had to comment out to compile
	if (direct == true)
		a = 2;
	if ((heredoc == 0 && file == NULL) || file[a] == '<' || file[a] == '>' 
		|| file[a] == '\0' || file[a] == '\n' || file[a] == '|')
	{
		printf("minishell: syntax error near '<<'\n");
		return (true);
	}
	return (false);
}

void	ft_hdcount(char **temp, t_info **info, char **inputs)
{
	int	i;
	char	**check;
	
	i = 0;
	check = ft_split(inputs[0], '|');
	while (temp[i] != NULL)
	{
		printf("string == %s\n", temp[i]);
		if (ft_strncmp(temp[i], "<<", 2) == 0)
		{
			if (ft_strlen(temp[i]) >ft_strlen("<<"))
				(*info)->panic = ft_validheredoc(info, true, (*info)->hdcount, temp[i]);
			else
				(*info)->panic = ft_validheredoc(info, false, (*info)->hdcount, temp[i + 1]);
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
	if ((*info)->hdcount == 1 && check[1] == NULL 
			&& (*info)->catcount == 0)
		(*info)->panic = true;
	ft_freearray(check);
}

char	**ft_checkheredoc(char **inputs, t_info **info)
{
	char	**heredocarray;
	char	**temp;

	(*info)->panic = false;
	temp = ft_split(inputs[0], ' ');
	ft_hdcount(temp, info, inputs);
	if ((*info)->panic == true && (*info)->hdcount == 0)
	{
		ft_freearray(temp);
		return (NULL);
	}
	if ((*info)->hdcount == 0)
	{
		ft_freearray(temp);
		return (inputs);
	}
	(*info)->first = true;
	heredocarray = ft_heredocarray((*info)->hdcount, temp); //extract from inputs
	ft_heredocexecute(heredocarray, info); //while loop - see notes
	ft_freearray(temp);//is this helping?
	return(NULL);
}

void	ft_heredocmain(char *cmdline, t_info **info)
{
	int	i;
	
	i = 0;
	(*info)->hdcount = 0;
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
