/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocprocess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:28:00 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/06 17:28:02 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Builtins.h"
#include "../Libft/libft.h"
#include <sys/ioctl.h>
int	global = 0;

static void	ft_hdsigint(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(STDOUT_FILENO, TIOCSTI, "\n");
	global = 3;
}

void	ft_hdprocess(t_info **info, char **hdarray, int hdcount)
{
	int	runhere;
	int	i;
	char	*input;

	i = 0;
	runhere = 0;
	global = 0;
	while (global == 0 && runhere != (*info)->hdcount)
	{
		input = (ft_strdup(readline("heredoc<< "), 1));
		if (ft_strncmp(hdarray[i], input, ft_strlen(hdarray[i])) == 0)
		{
			i++;
			runhere++;
			free(input);
		}
		else 
		{
			(*info)->collect = ft_strjoin((*info)->collect, input, 0);
			(*info)->collect = ft_strjoin((*info)->collect, "\n", 2);
		}
	}
	global = 0;
}

void	ft_heredocexecute(char **hdarray, t_info **info)
{
	(*info)->collect = malloc(sizeof(char) * 1);
	(*info)->collect[0] = '\0';
	signal(SIGINT, ft_hdsigint);
	ft_hdprocess(info, hdarray, (*info)->hdcount);
	signal(SIGINT, ft_ctrlc);
	if ((*info)->catcount == 1 && global == 0)
		printf("%s", (*info)->collect);
	if ((*info)->collect)
		free((*info)->collect);
	ft_freearray(hdarray);
}
