/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:46 by jelliott          #+#    #+#             */
/*   Updated: 2024/03/20 22:30:59 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
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
		signal(SIGQUIT, ft_ctrlc); 
		signal(SIGINT, ft_ctrlc);
		if (ft_whichsignalfunction(buf, &info) == 2)
		{
			signal(SIGINT, ft_ctrlc2);
			signal(SIGQUIT, ft_ctrlc2);
		}
		if (has_unmatched_quotes(buf))
		{
			ft_putstr_fd("unmatched quote\n", 2);
			continue;
		}
		if (is_whitespace(buf))
			continue ;
		if (ft_strncmp(buf, "\"\"", 2) == 0)
		{ 
        	printf("Error: Command '' not found.\n");
			info->exitstatus = 127;
			continue;
		}
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
	return(0);
}
