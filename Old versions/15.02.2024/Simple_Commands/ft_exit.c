/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:25:59 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:26:01 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"
//can exit alone or with a numerical variable
//when there is a numerical variable - echo $? will print the exit status [is this relevant?]
//this function primarily deals with exit alone
void    ft_exit(char *arraystring, char **cmdargs, t_env **head, t_info **info)
{
	int	status;

	status = 0;
	if (cmdargs[2] != NULL)
	{
		write(2, "minishell: exit: too many arguements", ft_strlen("minishell: exit: too many arguements"));
		exit(1);
	}
	printf("exit\n");
	if (cmdargs[1] == NULL)
		exit(0); //or pick up the exit status from somewhere
	else
		status = ft_atoi(cmdargs[1]) % 256;
	if (status < 0)
		status += 256;
	exit(status);
}