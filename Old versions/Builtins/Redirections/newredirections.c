/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newredirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:34:38 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/30 14:34:40 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Builtins.h"
#include <fcntl.h>
#include <sys/stat.h>

int	ft_getfiledescriptor(char *redir, char *file)
{
	int	file_descriptor;

	if (redir[0] == '>' && redir[1] == '\0')
		file_descriptor = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else if (redir[0] == '>' && redir[1] == '>')
		file_descriptor = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	else if (redir[0] == '<' && redir[1] == '\0')
		file_descriptor = open(file, O_RDONLY);
	return (file_descriptor);
}

int	ft_redirtype(char *redir)
{
	if (redir[0] == '>' && redir[1] == '\0')
		return (1);
	else if (redir[0] == '>' && redir[1] == '>')
		return (1);
	else if (redir[0] == '<' && redir[1] == '\0')
		return (0);
	return (-1);
}

//O_WRONLY | O_CREAT | O_TRUNC: Flags for opening the file. In this case:
//O_WRONLY: Open the file for writing only.
//O_CREAT: Create the file if it doesn't exist.
//O_TRUNC: Truncate the file to zero length if it already exists.
//S_IRUSR | S_IWUSR: File permission flags. In this case:
//S_IRUSR: Read permission for the owner.
//S_IWUSR: Write permission for the owner.
void	ft_simpleredir(char **redirarray, t_info **info)
{
	int	file_descriptor;
        int	fd[2];
        int	pid;
        int	status;
        int	redirtype;

	printf("redirarray[1]%s\n", redirarray[1]);
	printf("redirarray[2]%s\n", redirarray[2]);
        file_descriptor = ft_getfiledescriptor(redirarray[1], redirarray[2]);
        redirtype = ft_redirtype(redirarray[1]);
        pipe(fd);
        fd[1] = file_descriptor;
        if ((pid = fork()) == 0)
        {
        	close(fd[0]);
        	dup2(fd[1], redirtype);
        	ft_inputs(redirarray[0], info);
        	close(fd[1]);
        	exit (0);
	}
        wait(&status);
}
