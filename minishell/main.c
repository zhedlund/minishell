/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:46 by jelliott          #+#    #+#             */
/*   Updated: 2024/03/22 15:35:37 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mainsignals(t_info **info, char *buf)
{
	signal(SIGQUIT, ft_ctrlc); 
	signal(SIGINT, ft_ctrlc);
	if (ft_whichsignalfunction(buf, info) == 2)
	{
		signal(SIGINT, ft_ctrlc2);
		signal(SIGQUIT, ft_ctrlc2);
	}
	if (g_signal == 130 || g_signal == 6)
	{
		if (g_signal == 130)
			(*info)->exitstatus = 130;
		if (g_signal == 6)
			(*info)->exitstatus = 0;
		g_signal = 0;
	}
}

int	main(void)
{
	static char	buf[1024];
	int			status;
	t_info		*info;
	t_env		*head;

	status = 0;
	head = NULL;
	info = ft_calloc(sizeof(t_info), 1);
	get_env(&head);
	while (get_cmd(buf, sizeof(buf), &head, &info) >= 0)
	{
		ft_heredocmain(buf, &info);
		ft_isitcat(buf, &info);
		ft_mainsignals(&info, buf);
		if (ft_disinherit(buf, &head, &info) == false && info->panic == false)
		{
			if (fork_process() == 0)
			{
				info->exiting = true;
				run_cmd(parse_cmd(buf, &info, &head), &head, &info);
			}
			wait(&status);
			if (WIFEXITED(status))
				info->exitstatus = WEXITSTATUS(status);
			status = info->exitstatus;
		}
		info->hdcount = 0;
		info->catcount = 0;
		unlink("/tmp/hdtemp");
	}
	rl_clear_history();
	free(info);
	ft_freelist(&head);
	return (0);
}
