/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdprocess.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:18:17 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/20 10:18:20 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
#include <sys/ioctl.h>

char	**ft_heredocarray(int heredoc, char **inputs)
{
	int			i;
	int			j;
	char		**hdarray;

	i = 0;
	j = 0;
	hdarray = (char **)malloc(sizeof(char *) * (heredoc + 1));
	hdarray[heredoc] = NULL;
	while (inputs[i] != NULL)
	{
		if (ft_strlen(inputs[i]) == ft_strlen("<<")
			&& ft_strncmp(inputs[i], "<<", 1) == 0)
		{
			hdarray[j] = ft_strdup(inputs[i + 1]);
			j++;
		}
		else if (ft_strlen(inputs[i]) > ft_strlen("<<")
			&& ft_strncmp(inputs[i], "<<", 1) == 0)
		{
			hdarray[j] = ft_strtrim((ft_strdup(inputs[i])), "<<");
			j++;
		}
		i++;
	}
	return (hdarray);
}

static void	ft_hdsigint(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(STDOUT_FILENO, TIOCSTI, "\n");
	g_signal = 3;
}

void	ft_hdprocess_prep(t_info **info, char **hdarray)
{
	int		i;
	char	*input;
	int		fd;

	fd = open("/tmp/hdtemp", O_WRONLY | O_CREAT, 0644);
	i = 0;
	(*info)->runhere = 0;
	input = NULL;
	g_signal = 0;
	ft_hdprocess(hdarray, info, fd, input);
	g_signal = 0;
	(*info)->hdcount = 0;
}

void	ft_heredocexecute(char **hdarray, t_info **info)
{
	signal(SIGINT, ft_hdsigint);
	ft_hdprocess_prep(info, hdarray);
	signal(SIGINT, ft_ctrlc);
	ft_freearray(hdarray);
}
