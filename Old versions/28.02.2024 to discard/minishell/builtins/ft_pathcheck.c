/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathcheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:42:30 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/22 21:36:27 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_shorten(const char	*file)
{
	int		count;
	char	*new;
	int		length1;
	int		length2;

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
	int		count;
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
		return (0);
	if (access(file, X_OK) != 0)
		return (1);
	return (2);
}

bool	ft_checkdirectory(char	*tocheck)
{
	struct stat	filestat;

	if (stat(tocheck, &filestat) == 0 
		&& S_ISDIR(filestat.st_mode))
	{
		printf("minishell: is a directory: %s\n", tocheck);
		return (true);
	}
	return (false);
}

char	*ft_pathcheck(char *pp, t_info **info, t_exec *exec_cmd, t_env **head)
{
	int	choice;

	if (ft_checkdirectory(pp) == true)
		return (NULL);
	choice = ft_choice(pp);
	if (ft_strlen(pp) >= ft_strlen("./") 
		&& ft_strncmp(pp, "./", ft_strlen("./")) == 0)
		(*info)->aout = true;
	if (choice == 0 || (*info)->aout == true)
		return (pp);
	else if (choice == 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(pp, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ft_multifree(head, info, exec_cmd);
		exit (127);
	}
	(*info)->stillexecute = true;
	return (ft_shorten(pp));
}

bool	ft_isitapath(char *input)
{
	int	a;

	a = 0;
	if (input == NULL)
		return (false);
	while (input[a] != '\0')
	{
		if (input[a] == '/')
			return (true);
		a++;
	}
	return (false);
}
