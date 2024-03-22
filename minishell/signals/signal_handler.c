/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:15:28 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/21 15:15:44 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	g_signal = 0;

void	ft_ctrlc2(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		rl_replace_line("\0", 0);
		g_signal = 4;
	}
	if (signal == SIGQUIT)
	{
		(void)signal;
		write(1, "\033[K", 3);
		g_signal = 2;
	}
}

/* Ctrl-c handle */
void	ft_ctrlc(int sig)
{
	if (sig == SIGQUIT)
	{
		(void)sig;
		rl_on_new_line();
		rl_redisplay();
		write(1, "\033[K", 3);
		rl_redisplay();
		g_signal = 6;
	}
	if (sig == SIGINT)
	{
		(void)sig;
		rl_replace_line("\0", 0);
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 130;
	}
}

//more investigations //one is it grep with one arguement?
	//2 what are the other commands?

int	ft_igreatertwo(char **signalarray, t_info **info, int ctrlc)
{
	if (ft_firstcommandcheck(signalarray[0], info) == 2
		&& (signalarray[1][0] == '>'
		|| signalarray[2][0] == '>'))
		ctrlc = 2;
	return (ctrlc);
}

int	ft_nopipe(char **signalarray, int i, t_info **info, char *buf)
{
	int	ctrlc;

	ctrlc = 0;
	if ((*info)->pipe == false && i == 1)
	{
		if (ft_identical(signalarray[0], "cat") == true
			|| ft_identical(signalarray[0], "wc") == true)
			ctrlc = 2;
	}
	if ((*info)->pipe == false && i == 2)
	{
		if (ft_identical(signalarray[0], "wc") == true
			&& ft_identical(signalarray[1], "-l") == true)
			ctrlc = 2;
		if (ft_greponearguement(buf) == true)
			ctrlc = 2;
	}
	if ((*info)->pipe == false && i > 2)
		ctrlc = ft_igreatertwo(signalarray, info, ctrlc);
	return (ctrlc);
}

int	ft_whichsignalfunction(char *buf, t_info **info)
{
	char	**signalarray;
	int		i;
	int		ctrlc;

	i = 0;
	ctrlc = 0;
	signalarray = ft_split(buf, ' ');
	while (signalarray[i] != NULL)
	{
		if (signalarray[i][0] == '|')
			(*info)->pipe = true;
		i++;
	}
	if ((*info)->pipe == true)
	{
		ctrlc = ft_firstcommandcheck(buf, info);
		ft_freearray(signalarray);
		return (ctrlc);
	}
	else
		ctrlc = ft_nopipe(signalarray, i, info, buf);
	if (ctrlc == 2)
		(*info)->firstcommandmix = false; 
	ft_freearray(signalarray);
	return (ctrlc);
}
