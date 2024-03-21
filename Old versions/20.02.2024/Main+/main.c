/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:46 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/15 12:14:48 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

/* Main */

int g_signal = 0;

int main(void)
{
	static char	buf[100];
	int			status; // variable to store exit status of child process
	t_info	*info;
	// Read and run input commands.
	info = ft_calloc(sizeof(t_info), 1);
	while (get_cmd(buf, sizeof(buf)) >= 0)
	{
		// cd is just an example, will call builtin functions here
		// if (is_builtin()) or similar
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ') 
		{
			// Chdir have to be run in the parent, has no effect if run in the child.
			buf[ft_strlen(buf) - 1] = 0; // chop \n
			if (chdir(buf + 3) < 0)
				ft_putstr_fd("cannot cd\n", 2);
			continue;
		}
		ft_heredocmain(buf, &info);
		if (info->panic == false)
		{
			if (fork_process() == 0)
				run_cmd(parse_cmd(buf, &info));
			wait(&status);
		}
		unlink("hdtemp");
	}
	free(info);
	return(0);
}
