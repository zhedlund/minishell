/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdexperiment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:36:11 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/18 16:36:13 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"
#include <sys/ioctl.h>

int	ft_hdexecute(char *endkey, char *cmd)
{
	char	*input;
	int	fd;

	fd = open(endkey, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = (ft_strdup(readline("heredoc<< ")));
		if (ft_strncmp(endkey, input, ft_strlen(endkey)) != 0)
			write(fd, input, ft_strlen(input));
		if (ft_strncmp(endkey, input, ft_strlen(endkey)) == 0)
			break ;
		write(fd, "\n", 1);
	}
	free(input);
	return (fd);
	//will have to use unlink later to get rid of the file
	//it doesn't automatically execute this first and can't cope with doubles
	//in a way, I'm tempted to execute this indepently creating the temporary file
	//then that can be used by other commands
	//slight concern that they will return that there is no such file...unless...truncate the one
	//already have so it is empty?
	//some of the earlier approach seems sensible
	//cat test | grep ft - doesn't work properly, very close

	//getinfo at the start - as per old approach
	//execute, then initial cat...just open the file...later cats - just open/append the file
	//then finally unlink the file - perhaps right at the end
}
