/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:20:04 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/15 12:20:07 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

/* Execution */

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

int	ft_choice(const char *file)
{
	int	count;
	bool	path;
	char	*new;
	int	length1;
	int	length2;

	count = 0;
	path = false;
	while (file[count] != '\0')
	{
		if (file[count] == '/')
			path = true;
		count++;
	}
	if (path == false)
		return (0);
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

char	*ft_pathcheck(char *potentialpath, t_info **info)
{
	int	choice;
	
	if (ft_checkdirectory(potentialpath) == true)
		return (NULL);
	choice = ft_choice(potentialpath);
	if (choice == 0)
		return (potentialpath);
	else if (choice == 1)
	{
		printf("minishell: ");
		printf("%s", potentialpath);
		printf( ": No such file or directory\n");
		return (NULL);
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
    exec_cmd->argv[0] = ft_pathcheck(exec_cmd->argv[0], info);
	if (ft_strncmp(exec_cmd->argv[0], "cd", ft_strlen(exec_cmd->argv[0])) == 0)
		ft_cd(exec_cmd->argv[0], exec_cmd->argv, head);
	else if (ft_strncmp(exec_cmd->argv[0], "env", ft_strlen(exec_cmd->argv[0])) == 0)
		ft_env(exec_cmd->argv[0], head);
	else if (ft_strncmp(exec_cmd->argv[0], "unset", ft_strlen(exec_cmd->argv[0])) == 0)
		ft_unset(exec_cmd->argv[0], exec_cmd->argv, head);
	else if (ft_strncmp(exec_cmd->argv[0], "exit", ft_strlen(exec_cmd->argv[0])) == 0)
		ft_exit(exec_cmd->argv[0], exec_cmd->argv, head);
	else if (ft_strncmp(exec_cmd->argv[0], "export", ft_strlen(exec_cmd->argv[0])) == 0)
		ft_export(exec_cmd->argv[0], exec_cmd->argv, head);
	else if (ft_strncmp(exec_cmd->argv[0], "pwd", ft_strlen(exec_cmd->argv[0])) == 0)
		ft_pwd(exec_cmd->argv[0], head);
    else if (ft_strncmp(exec_cmd->argv[0], "echo", ft_strlen(exec_cmd->argv[0])) == 0)
		ft_echo(exec_cmd->argv[0], exec_cmd->argv, head);
    else if ((*info)->unsetpath == true && (*info)->stillexecute != true)
	{
		printf("Minishell: %s: No such file or directory\n", exec_cmd->argv[0]);
		exit(0);
	}
	else    
		ft_execvp(exec_cmd->argv[0], exec_cmd->argv, head);
}
