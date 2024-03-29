/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:55:46 by zhedlund          #+#    #+#             */
/*   Updated: 2024/03/26 18:13:07 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtins_not_env(t_exec *exec_cmd, t_env **head, t_info **info)
{
	if (ft_identical(exec_cmd->argv[0], "cd") == true)
		ft_cd(exec_cmd, head, info);
	else if (ft_identical(exec_cmd->argv[0], "unset") == true)
		ft_unset(exec_cmd, head, info);
	else if (ft_identical(exec_cmd->argv[0], "exit") == true)
		ft_exit(exec_cmd, head, info);
	else if (ft_identical(exec_cmd->argv[0], "export") == true)
		ft_export(exec_cmd, head, info);
	else if (ft_identical(exec_cmd->argv[0], "pwd") == true)
		ft_pwd(head, info, exec_cmd); 
	else if (ft_identical(exec_cmd->argv[0], "echo") == true)
		ft_echo(exec_cmd, head, info);
}

void	ft_command_not_found(t_exec *exec_cmd, t_env **head, t_info **info)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, exec_cmd->argv[0], ft_strlen(exec_cmd->argv[0]));
	write(2, ": Command not found\n", ft_strlen(": Command not found\n"));
	(*info)->exitstatus = 127;
	ft_multifree(head, info, exec_cmd);
	exit (127);
}

void	ft_is_it_a_command(t_exec *exec_cmd, t_env **head, t_info **info)
{
	char	*check;

	if (exec_cmd->argv[0] != NULL 
		&& exec_cmd->argv[0][0] != '\0')
	{
		check = ft_strjoin("/bin/", exec_cmd->argv[0]);
		if (access(check, X_OK) != 0)
		{
			free(check);
			ft_command_not_found(exec_cmd, head, info);
		}
		free(check);
	}
}

void	ft_itisapath(t_exec *exec_cmd, t_env **head, t_info **info)
{
	if ((ft_identical("/bin/env", exec_cmd->argv[0]) == true)
		|| (ft_identical("/usr/bin/env", exec_cmd->argv[0]) == true))
	{
		exec_cmd->argv[0] = ft_shorten(exec_cmd->argv[0]);
		ft_env(head, info, exec_cmd);
	}
	exec_cmd->argv[0] = ft_pathcheck(exec_cmd->argv[0], info, exec_cmd, head);
	ft_execvp(exec_cmd, exec_cmd->argv, head, info);
}

void	ft_exiting(t_exec *exec_cmd, t_env **head, t_info **info)
{
	if (ft_strlen(exec_cmd->argv[0]) >= ft_strlen("./")
		&& ft_strncmp(exec_cmd->argv[0], "./", ft_strlen("./")) == 0)
		ft_execvp(exec_cmd, exec_cmd->argv, head, info);
	if (ft_isitapath(exec_cmd->argv[0]) == true)
		ft_itisapath(exec_cmd, head, info);
	ft_builtins_not_env(exec_cmd, head, info);
	ft_is_it_a_command(exec_cmd, head, info);
	ft_pathexperiment(exec_cmd, info, head);
	ft_execvp(exec_cmd, exec_cmd->argv, head, info);
}
