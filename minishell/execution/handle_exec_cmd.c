/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:55:46 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/22 21:23:50 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

/* exec_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void handle_exec_cmd(t_exec *exec_cmd, t_env **head, t_info **info)
{
	if (exec_cmd->argv[0] == 0)
        exit(0);
    exec_cmd->argv[0] = ft_pathcheck(exec_cmd->argv[0], info, exec_cmd, head);
	if (ft_strlen("cd") == ft_strlen(exec_cmd->argv[0]) 
			&&	ft_strncmp(exec_cmd->argv[0], "cd", ft_strlen(exec_cmd->argv[0])) == 0)
			ft_cd(exec_cmd->argv, head, info);
	else if (ft_strlen("env") == ft_strlen(exec_cmd->argv[0]) 
		&& (*info)->unsetpath == false 
			&& ft_strncmp(exec_cmd->argv[0], "env", ft_strlen(exec_cmd->argv[0])) == 0)
		ft_env(exec_cmd->argv[0], head, info, exec_cmd);
	else if (ft_strlen("unset") == ft_strlen(exec_cmd->argv[0]) 
				&&	ft_strncmp(exec_cmd->argv[0], "unset", ft_strlen(exec_cmd->argv[0])) == 0)
			ft_unset(exec_cmd->argv[0], exec_cmd, head, info);
	else if (ft_strlen("exit") == ft_strlen(exec_cmd->argv[0])
				&&	ft_strncmp(exec_cmd->argv[0], "exit", ft_strlen(exec_cmd->argv[0])) == 0)
		ft_exit(exec_cmd, head, info);
	else if (ft_strlen("export") == ft_strlen(exec_cmd->argv[0]) 
				&&	ft_strncmp(exec_cmd->argv[0], "export", ft_strlen(exec_cmd->argv[0])) == 0)
		ft_export(exec_cmd->argv, head, info);

	else if (ft_strlen("pwd") == ft_strlen(exec_cmd->argv[0])
			&&	ft_strncmp(exec_cmd->argv[0], "pwd", ft_strlen(exec_cmd->argv[0])) == 0)
		ft_pwd(head, info, exec_cmd); 
	else if (ft_strlen("echo") == ft_strlen(exec_cmd->argv[0]) 
				&&	ft_strncmp(exec_cmd->argv[0], "echo", ft_strlen(exec_cmd->argv[0])) == 0)
					ft_echo(exec_cmd->argv[0], exec_cmd, head, info); 
    else if (((*info)->unsetpath == true && (*info)->stillexecute != true))
	{
		write(2, "Minishell: ", ft_strlen("Minishell: "));
		write(2, exec_cmd->argv[0], ft_strlen(exec_cmd->argv[0]));
		write(2, ": Command not found\n", ft_strlen(": Command not found\n"));
		(*info)->exitstatus = 126;
		ft_multifree(NULL, head, info, exec_cmd);
		exit(126);
	}
	else 
		ft_execvp(exec_cmd, exec_cmd->argv, head, info);
}
