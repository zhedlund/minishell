/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:02:34 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/23 20:02:00 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_signals(t_info **info)
{
	if (g_signal != 0)
	{
		if (g_signal == 2 && (*info)->firstcommandmix == false)
			printf("Quit (core dumped)\n");
		else if (g_signal == 4)
			printf("\n");
		if (g_signal == 2 && (*info)->firstcommandmix == false)
			(*info)->exitstatus = 131;
		else if (g_signal != 2 && (*info)->firstcommandmix == false)
			(*info)->exitstatus = 130;
		else if (g_signal == 130)
			(*info)->exitstatus = 130;
		else
			(*info)->exitstatus = 0;
		g_signal = 0;
	}
}

/* buf: pointer to the buffer to store the input
 * buf_size: size of the buffer
 * return: 0 if input is not empty, -1 otherwise
 * note: the function is called by: main()
 */
int	get_cmd(char *buf, int buf_size, t_env **head, t_info **info)
{
	char	*input;

	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, ft_ctrlc);
	if (g_signal != 0)
		handle_signals(info);
	if (isatty(0))
		input = readline("minishell> ");
	else
		input = readline("");
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		ft_freelist(head);
		free(*info);
		exit(0);
	}
	ft_strlcpy(buf, input, buf_size);
	buf[buf_size - 1] = '\0';
	add_history(buf);
	free(input);
	return (0);
}

