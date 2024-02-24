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

//exit with exit status of the previous progamme
//or with the user entered value
//called from the overall parent process if 'exit' the only command
void	ft_exit(t_exec *exec_cmd, t_env **head, t_info **info)
{
	int		status;
	char	**cmdargs;

	cmdargs = exec_cmd->argv;
	status = 0;
	if (cmdargs[1] != NULL && cmdargs[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguements", 2);
		ft_multifree((*info)->expanded, head, info, exec_cmd);
		exit(1);
	}
	if (cmdargs[1] == NULL)
	{
		status = (*info)->exitstatus;
		ft_multifree((*info)->expanded, head, info, exec_cmd);
		exit(status);
	}
	else
		status = ft_atoi(cmdargs[1]) % 256;
	if (status < 0)
		status += 256;
	ft_multifree((*info)->expanded, head, info, exec_cmd);
	exit(status);
}
