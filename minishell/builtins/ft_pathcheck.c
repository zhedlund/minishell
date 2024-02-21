/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathcheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:20:04 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/21 20:39:04 by zhedlund         ###   ########.fr       */
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
		write(2, "minishell: ", ft_strlen("minishell: ")); // why not use ft_putstr_fd?
		write(2, potentialpath, ft_strlen(potentialpath));
		write(2, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
		ft_multifree(NULL, head, info, exec_cmd);
		exit (127);
	}
	(*info)->stillexecute = true;
	return (ft_shorten(potentialpath));
}
