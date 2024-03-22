/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:24:21 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/19 21:10:23 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

//using errno to print the error message, but need to check if we are allowed to use this
//problem here that there is no variable to give - same with some other builtin functions
//this function uses getcwd to store the pwd in a string and then prints the string
void	ft_multifree(char *arraystring, t_env **head, t_info **info, t_exec *exec_cmd)
{
	int	check;
	char	**cmdargs;

	cmdargs = exec_cmd->argv;
	check = 1;
	rl_clear_history();
	//clear_history();
	if (arraystring == NULL)
		check = 0;
	while (cmdargs[check] != NULL)
	{
		free (cmdargs[check]);
		check++;
	}
	//if ((*info)->expanded != NULL)
	//	free((*info)->expanded);
	ft_freelist(head);
	free((*info));
	if (arraystring != NULL)
		free(arraystring);
	free(exec_cmd);
}

void    ft_pwd(t_env **head, t_info **info, t_exec *exec_cmd)
{
	char	store[PATH_MAX];
	char	*path;
	int	i;
	
	i = 0;
	path = getcwd(store, sizeof(store));
	if (path)
	{
		while (path[i] != '\0')
		{
			write(1, &path[i], 1);
			i++;
		}
	}
	else
		printf("%s", strerror(errno));
	write(1, "\n", 1);
	(*info)->exitstatus = 0;
	//free((*info)->expanded);
	ft_multifree(NULL, head, info, exec_cmd);
	exit(0);
}