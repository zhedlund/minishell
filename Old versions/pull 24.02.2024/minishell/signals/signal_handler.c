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

#include "../minishell_tree.h"

int g_signal = 0;

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
        	write(1, "\033[K", 3); //"\033[K" is an escape code that means clear the line (it prevents a ghostly ^\ from appearing)
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
        write(1, "\033[K", 3); //"\033[K" is an escape code that means clear the line (it prevents a ghostly ^\ from appearing)
		rl_redisplay();
    }
	if (sig == SIGINT)
	{
		(void)sig;
		rl_replace_line("\0", 0);
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	ft_whichsignalsub(char *signalarray, int ctrlc, char *buf, t_info **info)
{
	if (signalarray[0] != '|')
		(*info)->allcat = false;
	if (ft_strncmp(signalarray, "grep", ft_strlen(buf)) == 0)
		return (2);
	if (ft_strncmp(signalarray, "yes", ft_strlen(buf)) == 0)
		return (2);
	return (ctrlc);
}

int	ft_whichsignalfunction(char *buf, t_info **info)
{
	char	**signalarray;
	int	i;
	int	ctrlc;
	
	i = 0;
	ctrlc = 0;
	signalarray = ft_split(buf, ' ');
	(*info)->allcat = true;
	while (signalarray[i] != NULL)
	{
		if (ft_strncmp(signalarray[i], "cat", ft_strlen(buf)) == 0)
			ctrlc = 2; //include the options here and return true or false
		else if (ft_strncmp(signalarray[i], "wc", ft_strlen(buf)) == 0)
		{
			ctrlc = 2;
			if (signalarray[i + 1] != NULL && signalarray[i + 1][0] != '|')
				i++;
		}
		else
			ctrlc = ft_whichsignalsub(signalarray[i], ctrlc, buf, info);
		i++;
	}
	ft_freearray(signalarray);
	return (ctrlc);
}
