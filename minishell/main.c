/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:46 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/25 21:35:07 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_doublequotes(char **cmdargs, int a)
{
	bool	space;
	int	i;
	char	dqq;
	char	*dq;

	dqq = 34;
	dq = &dqq;
	i = 0;
	space = false;
	cmdargs[a] = ft_strtrim(cmdargs[a], dq);
	if (cmdargs[a][0] == '\0')
		i = 1;
	while (cmdargs[a][i] != '\0')
	{
		while (cmdargs[a][i] == 34)
			i++;
		if (cmdargs[a][i] == '\0')
			i++;
		printf("%c", cmdargs[a][i]);
		i++;
	}
}


int main(void)
{
	static char	buf[1024];
	int			status;
	t_info		*info;
	t_env		*head;
	char	*bufex;
	char	dqq;
	char	*dq;
	const char	*test;

	dqq = 34;
	dq = &dqq;
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
		bufex = ft_strdup(buf);
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
		printf("newbuf == %s\n", buf);
		test = ft_countquotes(bufex, buf);
		if (is_whitespace(buf))
			continue ;
		printf("test == %s\n", test);
		//bufex = ft_strtrim(buf, dq);
		//printf("bufex == %s\n", bufex);
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
		info->hdcount = 0;
		info->catcount = 0;
		unlink("/tmp/hdtemp");
	}
	rl_clear_history();
	free(info);
	ft_freelist(&head);
	return(0);
}
