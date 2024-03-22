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
#include "../minishell.h"

bool	ft_charerror(char **cmdargs)
{
	int	a;

	a = 1;
	while (cmdargs[1][a] != '\0')
	{
		if (cmdargs[1][a] < 48 || cmdargs[1][a] > 57) 
		{
			printf("ERROR\n");
			return (true);
		}
		a++;
	}
	return (false);
}

bool	ft_exiterrors(char **cmdargs, t_info **info)
{
	bool		error;
	size_t		a;

	a = ft_strlen("9223372036854775807");
	error = false;
	if (cmdargs[1][0] == '-')
		a++;
	if (cmdargs[1][0] != '-' 
		&& ft_strlen(cmdargs[1]) > ft_strlen("9223372036854775807"))
		error = true;
	else if (cmdargs[1][0] != '-' 
		&& ft_strlen(cmdargs[1]) == ft_strlen("9223372036854775807")
		&& ft_strncmp(&cmdargs[1][0], "9223372036854775807", a) > 0)
		error = true;
	else if (cmdargs[1][0] == '-' && ft_strlen(&cmdargs[1][1]) > a)
		error = true;
	else if (cmdargs[1][0] == '-' && ft_strlen(&cmdargs[1][1]) == a
		&& ft_strncmp(&cmdargs[1][1], "9223372036854775808", a) > 0)
		error = true;
	if ((*info)->exiting == false)
		error = true;
	if (error == true)
		printf("ERROR\n");
	return (error);
}

signed long long	est(signed long long status, char **cmdargs, t_info **info)
{
	if (status < 0)
		status += 256;
	if (ft_charerror(cmdargs) == true)
		status = 2;
	else if (ft_exiterrors(cmdargs, info) == true)
		status = 255;
	if ((*info)->exiting == false)
		printf("exit");
	return (status);
}

void	ft_toomanyargs(t_info **info, t_env **head, t_exec *exec_cmd)
{
	ft_putstr_fd("minishell: exit: too many arguements", 2);
	if ((*info)->exiting == false)
		printf("exit");
	ft_multifree((*head)->expanded, head, info, exec_cmd);
	exit(1);
}

//exit with exit status of the previous progamme
//or with the user entered value
//called from the overall parent process if 'exit' the only command
void	ft_exit(t_exec *exec_cmd, t_env **head, t_info **info)
{
	signed long long		status;
	char					**cmdargs;
	int						a;

	a = 0;
	cmdargs = exec_cmd->argv;
	status = 0;
	if (cmdargs[1] != NULL && cmdargs[2] != NULL)
		ft_toomanyargs(info, head, exec_cmd);
	if (cmdargs[1] == NULL)
	{
		status = (*info)->exitstatus;
		if ((*info)->exiting == false)
			printf("exit");
		ft_multifree((*head)->expanded, head, info, exec_cmd);
		exit(status);
	}
	else
	{
		status = ft_atoi(cmdargs[1]) % 256;
		status = est(status, cmdargs, info);
		ft_multifree((*head)->expanded, head, info, exec_cmd);
		exit(status);
	}
}
