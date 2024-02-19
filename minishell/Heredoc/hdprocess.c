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
#include "../minishell_tree.h"
#include <sys/ioctl.h>

char	**ft_heredocarray(int heredoc, char **inputs)
{
	int	i;
	int	j;
	char	**hdarray;

	i = 0;
	j = 0;
	hdarray = (char **)malloc(sizeof(char *) * (heredoc + 1));
	hdarray[heredoc] = NULL;
	while (inputs[i] != NULL)
	{
		if (ft_strncmp(inputs[i], "<<", 1) == 0)
		{
			hdarray[j] = ft_strdup(inputs[i + 1]);
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

void	ft_hdprocess(t_info **info, char **hdarray)
{
	int	runhere;
	int	i;
	char	*input;
	int	fd;

	fd = open("/tmp/hdtemp", O_WRONLY | O_CREAT, 0644);
	i = 0;
	runhere = 0;
	g_signal = 0;
	while (g_signal == 0 && runhere != (*info)->hdcount)
	{
		input = (readline("heredoc<< "));
		if (!input)
			break ;
		if (ft_strncmp(hdarray[i], input, ft_strlen(hdarray[i])) != 0)
			write(fd, input, ft_strlen(input));
		if (ft_strncmp(hdarray[i], input, ft_strlen(hdarray[i])) == 0)
		{
			i++;
			runhere++;
		}
		free (input);
		if (runhere == (*info)->hdcount)
			break ;
		write(fd, "\n", 1);	
	}
	g_signal = 0;
	(*info)->hdcount = 0;
}

void	ft_heredocexecute(char **hdarray, t_info **info)
{
	signal(SIGINT, ft_hdsigint);
	ft_hdprocess(info, hdarray);
	signal(SIGINT, ft_ctrlc);
	ft_freearray(hdarray);
}
