/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirexecute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:33:50 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/19 11:33:58 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Builtins.h"

//this function gathers information required for the dup2 calls - that set up redirection
//then makes the dup2 calls
//as these are happening within the child process, they alter the enironment of the child process
//this alteration is taken care of by the operating system after the dup2 call
int ft_setupredirection(char *filename, char *redircmd)
{
    int	fd[2];
    char kind;

    kind = ft_findtype(redircmd);
    fd[1] = ft_fdtype(filename, redircmd);
    fd[0] = ft_openfile(filename, kind);
    //ft_fdtype(kind);
    //dup2 function to setup inputs and outputs

}

//this function opens files/creates in readiness for their being used as input of output
//it relates to a heredoc subfunction that creates a heredoc shell and collects command line input until the end is reached
int ft_openfile(char *filename, int kind)
{
	{
	int	fd[2];

	//if (type == REDIR_HEREDOC)
	//{
	//	if (pipe(fd) == -1)
	//		fd[0] = -1;
	//	else
	//	{
	//		write(fd[1], file, ft_strlen(file));
	//		close(fd[1]);
	//	}
	//}
	else if (type == 'b')
		fd[0] = open(file, O_RDONLY, 0);
	else if (type == 'a')
		fd[0] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 'd')
		fd[0] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	//if (fd[0] == -1)
	//	print_error_errno(SHELL_NAME, file, NULL);
	return (fd[0]);
}
    
    
    //github.com/tjensen42/42-minishell/blob/main/src/redir/redir.c
}

//!!!!!!rewrite
//this function returns an int that tells us what sort of file descriptor we need
//based on the commandline input
//custom, input, or output 
//we need this information for the dup2 function to set input/output of the overall child process
int ft_fdtype(int kind)
{

	long	fd;
	int		i;

	fd = 0;
	i = 0;
	if (ft_isdigit(redir[0]))
	{
		while (ft_isdigit(redir[i]))
		{
			fd = fd * 10 + (redir[i] - '0');
			if (fd > INT_MAX)
			{
				print_error(SHELL_NAME, redir, NULL,
					"file descriptor out of range");
				return (ERROR);
			}
			i++;
		}
		return ((int) fd);
	}
	else if (type == 'b'|| type == 'd')
		return (STDOUT_FILENO);
	else if (type == 'a'|| type == 'c')
		return (STDIN_FILENO);
	return (ERROR);
}

//this function determines what type of redirection has been commanded
//we skip over ant intergers that might appear before a redirection sign like with 2>
//2> redirects the error output of the command to the file
//- << requires the creation of a heredoc (perhaps a list of char strings?)
//and heredoc shell that returns the heredoc when the end has been reached, the end is the input after << 
//!!!!still need to do the h file for the redirection terms
char ft_findtype(char *type)
{
    int i;

    i = 0;
    while (type[i] //== int) //how to check for this - use ascii
        i++;
    if (type[i] == '<' && type[i + 1] == '\0')
        return (a);
    else if (type[i] == '>' && type[i + 1] == '\0')
        return (b);
    else if (type[i] == '<' && type[i + 1] == '<')
        return (c);
    else if (type[i] == '>' && type[i + 1] == '>')
        return (d); 
    //else
        //error function
}

