/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:02:34 by zhedlund          #+#    #+#             */
/*   Updated: 2024/03/21 23:00:47 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signals(t_info **info)
{
	if (g_signal != 0)
	{
		if (g_signal == 2 && (*info)->firstcommandmix == false)
			printf("Quit (core dumped)\n");
		else if (g_signal == 4)
			printf("\n");
		if (g_signal == 2 
			&& (*info)->firstcommandmix == false)
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

static int	handle_dot(char *buf, t_info **info)
{
	if (buf[1] == '/' && buf[2])
		return (0);
	else if (!buf[1])
	{
		printf("minishell: .: filename argument required\n");
		printf(".: usage: filename [arguments]\n");
		(*info)->exitstatus = 2;
	}
	else
	{
		printf("%s: command not found\n", buf);
		(*info)->exitstatus = 127;
	}
	return (1);
}

static int	input_error(char *buf, t_info **info)
{
	if (buf[0] == '\0' || is_whitespace(buf))
		return (1);
	if (has_unmatched_quotes(buf))
	{
		ft_putstr_fd("Unmatched quote\n", 2);
		(*info)->exitstatus = 2;
		return (1);
	}
	if ((buf[0] == '/' && !buf[1])
		|| (buf[0] == '.' && buf[1] == '/' && !buf[2]))
	{
		printf("minishell: %s: Is a directory\n", buf);
		(*info)->exitstatus = 126;
		return (1);
	}
	if (buf[0] == '.')
		return (handle_dot(buf, info));
	if (ft_identical(buf, "\"\""))
	{
		printf("Command '' not found\n");
		(*info)->exitstatus = 127;
		return (1);
	}
	return (0);
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
	if (input_error(input, info))
		return (get_cmd(buf, buf_size, head, info));
	free(input);
	return (0);
}
