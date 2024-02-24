/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:25:59 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/22 21:14:52 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

//can exit alone or with a numerical variable
//when there is a numerical variable - echo $? will print the exit status [is this relevant?]
//this function primarily deals with exit alone
//void	ft_exitfree(t_exec *exec_cmd, t_env **head, t_info **info)
//{
//	free((*info));
//	ft_freelist(head);
	//ft_freearray(cmdargs);
//}

void    ft_exit(t_exec *exec_cmd, t_env **head, t_info **info)
{
	int	status;
	char	**cmdargs;

	cmdargs = exec_cmd->argv;
	status = 0;
	if (cmdargs[1] != NULL && cmdargs[2] != NULL)
	{
		printf("cmdargs[2] == %s\n", cmdargs[2]);
		write(2, "minishell: exit: too many arguements", ft_strlen("minishell: exit: too many arguements"));
		ft_multifree((*info)->expanded, head, info, exec_cmd);
		//ft_exitfree(cmdargs, head, info);
		exit(1);
	}
	printf("exit\n");
	if (cmdargs[1] == NULL)
	{
		ft_multifree((*info)->expanded, head, info, exec_cmd);
		//ft_exitfree(cmdargs, head, info);
		exit(0); //or pick up the exit status from somewhere
	}
	else
		status = ft_atoi(cmdargs[1]) % 256;
	if (status < 0)
		status += 256;
	ft_multifree((*info)->expanded, head, info, exec_cmd);
	//rl_clear_history();
	//ft_exitfree(cmdargs, head, info);
	exit(status);
}