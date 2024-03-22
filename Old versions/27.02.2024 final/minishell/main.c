/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:46 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/22 21:01:34 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	static char	buf[PATH_MAX];
	int			status;
	t_info		*info;
	t_env		*head;
	const char	*test;
	char	*bufex;

	status = 0;
	head = NULL;
	info = ft_calloc(sizeof(t_info), 1);
	get_env(&head);
	while (get_cmd(buf, sizeof(buf), &head, &info) >= 0)
	{
		signal(SIGQUIT, ft_ctrlc); 
		signal(SIGINT, ft_ctrlc);
		bufex = buf;
		if (ft_whichsignalfunction(buf, &info) == 2)
		{
			signal(SIGINT, ft_ctrlc2);
			signal(SIGQUIT, ft_ctrlc2);
		}
		if (g_signal == 130 || g_signal == 6)
		{
			if (g_signal == 130)
				info->exitstatus = 130;
			if (g_signal == 6)
				info->exitstatus = 0;
			g_signal = 0;
			
		}
		if (has_unmatched_quotes(buf))
		{
			ft_putstr_fd("unmatched quote\n", 2);
			test = buf;
			continue;
		}
		else
			test = ft_countquotes(bufex, buf);
		ft_heredocmain(buf, &info);
		ft_isitcat(buf, &info);
		if (is_whitespace(buf))
			continue ;
		if (ft_disinherit((char *)test, &head, &info) == false && info->panic == false)
		{
				if (fork_process() == 0)
				{
					info->exiting = true;
					run_cmd(parse_cmd((char *)test, &info, &head), &head, &info);
				}
				wait(&status);
				if (WIFEXITED(status))
					info->exitstatus = WEXITSTATUS(status);
				status = info->exitstatus;
		}
		free((char *)test);
		info->hdcount = 0;
		info->catcount = 0;
		unlink("/tmp/hdtemp");
		//anything else like this that needs resetting?
	}
	rl_clear_history();
	free(info);
	ft_freelist(&head);
	return(0);
}
