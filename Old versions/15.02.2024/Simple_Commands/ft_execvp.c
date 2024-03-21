/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:59:32 by zhedlund          #+#    #+#             */
/*   Updated: 2024/01/05 20:42:22 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"
#include <sys/ioctl.h>

/* Function to allocate memory for the full path of a command
 * @param token: path to command
 * @param file: command to execute
 * @return: full path of command
 */
static char	*allocate_full_path(const char *token, const char *file)
{
	size_t	path_len;
	size_t file_len;
	char *full_path;

	path_len = ft_strlen(token);
	file_len = ft_strlen(file);
	if ((path_len + file_len + 2) > (PATH_MAX + 1)) // PATH_MAX is defined in limits.h, exit code for this?
	{
		write(2, "Path length exceeds maximum allowed.\n", ft_strlen("Path length exceeds maximum allowed.\n"));
		return (NULL);
	}
	full_path = malloc((path_len + file_len + 2) * sizeof(char));
	if (!full_path)
		return NULL;
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
    char *path = getenv("PATH");
    char *path_copy = ft_strdup(path);
    char *token = ft_strtok(path_copy, ":");
    char *full_path = NULL;

    while (token != NULL)
	{
        full_path = allocate_full_path(token, file);
        if (full_path != NULL && access(full_path, X_OK) == 0)
		{
            free(path_copy);
            return full_path;
        }
        free(full_path); // Freeing if access fails or allocation fails
        token = ft_strtok(NULL, ":");
    }
    free(path_copy);
    return (NULL);
}

/* Function to execute a simple command w options. Works similar to execvp
 * @param file: command to execute
 * @param argv: arguments for the command
 * @return: 0 if successful, -1 if not
 */
void ft_execvp(const char *file, char *const argv[], t_env **head, t_info **info)
{
	char *full_path;
	int	pid;
	int	status;

	//is this required? /bin/a is the only time I have triggered it and that's already taken care of
	//if (!file || !argv)
	//{
	//	printf("Invalid arguments.\n");
	//	return (-1);
	//}
	full_path = find_cmd_path(file);
	if (full_path == NULL)
	{
		write(2, "Command not found: ", ft_strlen("Command not found: "));
		write(2, file, ft_strlen(file));
		write(2, "\n", ft_strlen("\n"));
		exit (127);
	}
	else if (access(full_path, X_OK) != 0)
	{
		write(2, "Permission denied: ", ft_strlen("Permission denied: "));
		write(2, full_path, ft_strlen(full_path));
		write(2, "\n", ft_strlen("\n"));
		//perror(access); what is the exit code?
	}
	else
	{
			if (execve(full_path, argv, NULL) == -1)
			{
					perror("execve");
					free(full_path);
					exit(2);
			}

	}
	free(full_path); // Free memory allocated by find_command_path
	(*info)->exitstatus = 0;
	//exit (0); //this doesn't seem to make a diffference, but it should
}