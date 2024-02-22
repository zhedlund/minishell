/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:22:47 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/19 20:36:09 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

//works for expansion
//still need to work out exit statuses
void	ft_printout(int a, char **cmdargs)
{
		while (cmdargs[a] != NULL)
		{
			/*if (ft_strlen("$?") == ft_strlen(cmdargs[a])
				&& ft_strncmp(cmdargs[a],"$?", ft_strlen("$?")) == 0)
					printf("%d", (*info)->exitstatus);
			else*/
			printf("%s", cmdargs[a]);
			if (cmdargs[a + 1] != NULL)
				printf(" ");
			a++;
		}
		printf("\n");
}

void    ft_echo(char *arraystring, t_exec *exec_cmd, t_env **head, t_info **info)
{
	int	a;
	bool	newline;
	char	**cmdargs;

	newline = true;
	a = 1;
	cmdargs = exec_cmd->argv;
	if (cmdargs[1] == NULL)
	{
		printf("cmdargs[1] == NULL\n");
		write(1, "\n", 1);
	}
	else if (cmdargs[1][0] == '-' && cmdargs[1][1] == 'n')
	{
		newline = false;
		a = 2;
		//check = 2;
	}
	else if (newline == false && cmdargs[2] == NULL)
	{
		printf("newline == false && cmdargs[2] == NULL\n");
		write(1, "\n", 1);
	}
	ft_printout(a, cmdargs);
	//if (newline == true)
	//{
		//printf("newline == true\n");
		//write(1, "\n", 1);
	//}
	(*info)->exitstatus = 0;
	//if ((*info)->inchild == true)
	//{
		ft_multifree(arraystring, head, info, exec_cmd);
		exit(0);
	//}
}