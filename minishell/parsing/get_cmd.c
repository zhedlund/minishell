/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:02:34 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/21 22:08:08 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

/* buf: pointer to the buffer to store the input
	nbuf: size of the buffer
	return: 0 if input is not empty, -1 otherwise
	note: the function is called by: main()
 */

int get_cmd(char *buf, int buf_size, t_env **head, t_info **info)
{
	char	*input;

	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, ft_ctrlc);
	if (g_signal != 0)
	{
		if (g_signal == 2 && (*info)->allcat == true)
			printf("Quit (core dumped)\n");
		if (g_signal == 4)
			printf("\n");
		g_signal = 0;
		//(*info)->exitstatus = 131;
	}
	if (isatty(0)) // checks if connected to stdin (fd 0)
		input = readline("minishell> "); // read input w promt - interactive mode
	else
		input = readline(""); // read input w/o promt - non-interactive mode
	if (input == NULL) //for ctrl_d, ...export 1 | export 1 | export 1
	{
		printf("exit\n");
		ft_freelist(head);
		free(*info);
		exit(0);
	}
	ft_strlcpy(buf, input, buf_size); // copy input to buf
	buf[buf_size - 1] = '\0'; // null-terminated string
    add_history(buf); // Add input to history
    free(input); // Free memory allocated by readline()
	return (0);
}
