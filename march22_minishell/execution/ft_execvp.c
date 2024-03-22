/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:59:32 by zhedlund          #+#    #+#             */
/*   Updated: 2024/03/22 14:46:37 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Function to allocate memory for the full path of a command
 * @param token: path to command
 * @param file: command to execute
 * @return: full path of command
 */
static char	*allocate_full_path(const char *token, const char *file)
{
	size_t	path_len;
	size_t	file_len;
	char	*full_path;

	path_len = ft_strlen(token);
	file_len = ft_strlen(file);
	if ((path_len + file_len + 2) > (PATH_MAX))
	{
		printf("Path length exceeds maximum allowed.\n");
		return (NULL);
	}
	full_path = malloc((path_len + file_len + 2) * sizeof(char));
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, token);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, file);
	return (full_path);
}

/* Function to find the full path of a command
 * @param file: command to execute
 * @return: full path of command
 */
static char	*find_cmd_path(const char *file)
{
	char	*path;
	char	*path_copy;
	char	*token;
	char	*full_path;

	path = getenv("PATH");
	path_copy = ft_strdup(path);
	token = ft_strtok(path_copy, ":");
	full_path = NULL;
	while (token != NULL)
	{
		full_path = allocate_full_path(token, file);
		if (full_path != NULL && access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

static void	free_exit(const char *file, t_env **head, t_info **info,
						t_exec *exec_cmd)
{
	perror(file);
	ft_multifree(head, info, exec_cmd);
	exit(127);
}

/* Function to execute a simple command w options. Works similar to execvp
 * @param file: command to execute
 * @param argv: arguments for the command
 * @return: 0 if successful, -1 if not
 */
int	ft_execvp(t_exec *exec_cmd, char *const argv[], t_env **head, t_info **info)
{
	char		*full_path;
	const char	*file;

	file = exec_cmd->argv[0];
	if ((file[0] == '.' && file[1] == '/') || (file[0] == '/'))
		full_path = ft_strdup(file);
	else
		full_path = find_cmd_path(file);
	if (full_path == NULL)
		free_exit(file, head, info, exec_cmd);
	else if (access(full_path, X_OK) != 0)
	{
		perror(full_path);
		exit(126);
	}
	else if (execve(full_path, argv, NULL) == -1)
	{
		perror(full_path);
		exit(127);
	}
	free(full_path);
	return (-1);
}
