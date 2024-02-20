/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:20:04 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/20 21:12:00 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

char	*ft_shorten(const char	*file)
{
	int	count;
	char	*new;
	int	length1;
	int	length2;

	count = 0;
	while (file[count] != '\0')
		count++;
	length1 = count;
	while (file[count] != '/')
		count--;
	length2 = length1 - count;
	new = malloc(sizeof(char) * length2 + 1);
	count++;
	length2 = 0;
	while (file[count] != '\0')
	{
		new[length2] = file[count];
		count++;
		length2++;
	}
	new[length2] = '\0';
	return (new);
}

int	ft_choice(const char *file, t_info **info)
{
	int	count;
	bool	path;

	count = 0;
	path = false;
	while (file[count] != '\0')
	{
		if (file[count] == '/')
			path = true;
		count++;
	}
	if (path == false)
	{
		//not the right condition, but checking if a real command, maybe use full_path?
		//if (access(file, X_OK) != 0)
		//	(*info)->cmdnf = true;
		//else
		//	(*info)->cmdnf = false;
		return (0);
	}
	if (access(file, X_OK) != 0)
		return(1);
	return(2);
}

bool	ft_checkdirectory(char	*tocheck)
{
	struct stat	fileStat;

	if (stat(tocheck, &fileStat) == 0 
		&& S_ISDIR(fileStat.st_mode))
	{
		printf("minishell: is a directory: %s\n", tocheck);
		return (true);
	}
	return (false);
}

char	*ft_pathcheck(char *potentialpath, t_info **info, t_exec *exec_cmd, t_env **head)
{
	int	choice;
	
	if (ft_checkdirectory(potentialpath) == true)
		return (NULL);
	choice = ft_choice(potentialpath, info);
	if (ft_strlen(potentialpath) >= ft_strlen("./") &&
		ft_strncmp(potentialpath, "./", ft_strlen("./")) == 0)
		(*info)->aout = true;
	if (choice == 0 || (*info)->aout == true)
		return (potentialpath);
	else if (choice == 1)
	{
		write(2, "Minishell: ", ft_strlen("Minishell: "));
		write(2, potentialpath, ft_strlen(potentialpath));
		write(2, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
		ft_multifree(NULL, head, info, exec_cmd);
		exit (127);
	}
	(*info)->stillexecute = true;
	return (ft_shorten(potentialpath));
}

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
		ft_pwd(exec_cmd->argv[0], head, info, exec_cmd); 
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
