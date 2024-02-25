/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:25:07 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/19 21:34:53 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

void	ft_move(char *locate, t_env **head, t_info **info)
{
	char	*newpwd;

	newpwd = NULL;
	if (chdir(locate) != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		if (locate != NULL)
			ft_putendl_fd(locate, 2);
		((*info)->exitstatus = 1);
	}
	else
	{
		newpwd = ft_strjoin("PWD=", locate);
		ft_exportsub(newpwd, head);
		free(newpwd);
	}
}

void	ft_cd_finish(t_exec *exec_cmd, t_env **head, t_info **info)
{
	int	a;

	a = 0;
	if ((*info)->inchild == true)
	{
		ft_freelist(head);
		free((*info));
		free(exec_cmd);
		exit(0);
	}
	else
	{
		(*info)->exitstatus = 0;
		while (exec_cmd->argv[a] != NULL)
		{
			free(exec_cmd->argv[a]);
			a++;
		}
		free(exec_cmd);
	}
}

void	ft_cd_execute(t_exec *exec_cmd, t_env **head, t_info **info)
{
	char	*locate;
	char	**cmdarray;
	bool	move;

	move = true;
	locate = NULL;
	cmdarray = exec_cmd->argv;
	if (cmdarray[1] == NULL || cmdarray[1][0] == '~')
	{
		locate = ft_home(locate, head, info);
		if (ft_homeset(head) == false)
			move = false;
	}
	else if (ft_identical(cmdarray[1], "..") == true
		&& ft_identical(cmdarray[1], "/") == false)
		locate = ft_backone(locate);
	else if (ft_identical(cmdarray[1], ".") == true)
		locate = ft_cdsub(cmdarray[1]);
	else
		locate = cmdarray[1];
	if (move == true)
		ft_move(locate, head, info);
	if (locate && ft_identical(locate, cmdarray[1]) == false)
		free(locate);
}

void	ft_cd(t_exec *exec_cmd, t_env **head, t_info **info)
{
	char	**cmdarray;

	cmdarray = exec_cmd->argv;
	if (cmdarray[1] != NULL && cmdarray[2] != NULL)
	{
		(*info)->exitstatus = 1;
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
	}
	else
		ft_cd_execute(exec_cmd, head, info);
	ft_cd_finish(exec_cmd, head, info);
}
