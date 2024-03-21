/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:16:25 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:16:27 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef	BUILTINS_H
# define BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
# include "Libft/libft.h"

typedef struct s_info {
	int	catcount;
	int	hdcount;
	bool	panic;
	char	*collect; //collecting heredoc input
	char	**inputs;
	char	**redirarraycpy;
	char	*input;
	char	*oldpwd;
}	t_info;

void	ft_freearray(char **tofree);
//	static char *oldpath;
//	static char *oldoldpath;
void	ft_ctrlc(int sig);
//}	t_variables;
int	ft_inputs(char *input, t_info **info);
int	main(int argc, char **argv);
int	ft_echomain(int argc, char **argv);
int	ft_echo(char *arraystring);
int   ft_cd(char *arraystring, t_info **info);
int	ft_env(char *arraystring);
void    ft_exit(char *arraystring);
int	ft_export(char *arraystring);
int	ft_pwd(char *arraystring);
void    ft_unset(char *arraystring);
void	ft_siminput(char *input, t_info **info);
//redirections
int	ft_redirectionmain(char *arraystring, t_info **info);
bool	ft_checkpipe(char *arraystring, bool h, int i);
void	ft_simpleredir(char **redirarray, t_info **info);
void	ft_longredir(char **redirarray, char *command, t_info **info);
int	ft_redirtype(char *redir);
int	ft_getfiledescriptor(char *redir, char *file);
void	ft_doubleredirection(char **redirarray, t_info **info);
void	ft_longredirinitial(char **redirarray, t_info **info);
void ft_inend(char **unit, char	*file, char *redir, t_info **info);
char	**ft_checkheredoc(char **inputs, t_info **info);
///heredoc
void	ft_heredocexecute(char **hdarray, t_info **info);
char	**ft_checkheredoc(char **inputs, t_info **info);
char	*ft_newinputsarray(char **tmp, t_info **info);
char	**ft_heredocarray(int heredoc, char **inputs);

//pipes
int	pipeprep(char *input, t_info **info);
#endif
