/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:59:32 by zhedlund          #+#    #+#             */
/*   Updated: 2023/12/12 23:15:37 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to allocate memory for the full path of a command
 * @param token: path to command
 * @param file: command to execute
 * @return: full path of command
 */
char *allocate_full_path(const char *token, const char *file)
{
	size_t	path_len;
	size_t file_len;
	char *full_path;

	path_len = ft_strlen(token);
	file_len = ft_strlen(file);
	if ((path_len + file_len + 2) > (PATH_MAX + 1)) // PATH_MAX is defined in limits.h
	{
		printf("Path length exceeds maximum allowed.\n");
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
char *find_command_path(const char *file)
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
    return NULL;
}

/* Function to execute a simple command w options. Works similar to execvp
 * @param file: command to execute
 * @param argv: arguments for the command
 * @return: 0 if successful, -1 if not
 */
int execute_simple_command(const char *file, char *const argv[])
{
	char *full_path;

	if (!file || !argv)
	{
		printf("Invalid arguments.\n");
		return (-1);
	}
	full_path = find_command_path(file);
	if (full_path == NULL)
		printf("Command not found: %s\n", file);
	else if (access(full_path, X_OK) != 0)
		printf("Permission denied: %s\n", full_path);
	else if (execve(full_path, argv, NULL) == -1)
		perror("execve");
	free(full_path); // Free memory allocated by find_command_path
	return (-1);
}

/* simple main to test one comand + option.
The parser will probably return an array with commands similar to args[] here.*/

/*int main()
{
    char *args[] = {"ls", "-la", NULL}; // Example arguments
    execute_command("ls", args); // Example usage

    return (0);
}*/

/* main to test from command line. runs w simple command + option: ./a.out ls -la
If used with pipes or redirections, shell will take over, so it appears to work,
but won't work in minishell */

/*int main(int argc, char **argv)
{
    char *file;
    char **exec_args;
	int result;
	int i;
	
    if (argc < 2)
	{
        printf("Usage: %s <command> [options]\n", argv[0]);
        return (1);
    }
    file = argv[1]; // Extract the command from command-line arguments
    exec_args = malloc(argc * sizeof(char *)); // Allocate memory for exec_args
    if (!exec_args)
        return (1); // Return NULL if function, 1 in main
	i = 0;
	while (i < argc)
	{
		exec_args[i - 1] = argv[i];
		i++;
	}
    exec_args[argc - 1] = NULL; // Set the last element to NULL as required by execve
    result = execute_simple_command(file, exec_args); // Execute the command with options
    if (result != 0)
        printf("Failed to execute command: %s\n", file);
    free(exec_args); // Free allocated memory
    return 0;
}*/