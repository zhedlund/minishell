/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:23:46 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/19 16:51:14 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tree.h"

static char **expand_env_exit(char **argv, int status) {
    int i = 0;
    while (argv[i] != NULL) {
        if (ft_strcmp(argv[i], "$?") == 0) {
            // Replace "$?" with the string representation of the exit status
            free(argv[i]); // Free the original string
            argv[i] = ft_itoa(status); // Allocate memory and copy the exit status string
        }
        i++;
    }
    return argv;
}

char *expand_exit_status(char *input, int status)
{
    char **argv = ft_split(input, ' '); // Split the input string into an array of strings
    argv = expand_env_exit(argv, status);
    size_t total_length = 0;
	// Concatenate the array of strings into one string
    for (int i = 0; argv[i] != NULL; i++)
        total_length += ft_strlen(argv[i]) + 1; // Add 1 for space between words
    char *expanded_input = malloc(total_length + 1); // Add 1 for null terminator
    if (expanded_input == NULL) {
        ft_putstr_fd("Memory allocation failed\n", 2);
        exit(1);
    }
    expanded_input[0] = '\0'; // Initialize the string to empty
    for (int i = 0; argv[i] != NULL; i++)
	{
        ft_strcat(expanded_input, argv[i]);
        ft_strcat(expanded_input, " "); // Add space between words
        free(argv[i]); // Free memory allocated for each string
    }
    free(argv); // Free memory allocated for the array of strings
    return expanded_input;
}


/* 	Expands environment variables in the form of $USER, $HOME, etc. 
	returns a new array with the expanded variables
	note: called by parse_tokens()
	*/
char	**expand_env(char **argv, t_info **info)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '$' && argv[i][1] != '\0' && argv[i][1] != '?')
		{
			name = argv[i] + 1;
			value = getenv(name);
			if (value != NULL)
			{
				free(argv[i]);
				argv[i] = ft_strdup(value);
			}
		}
		/*if (argv[i][0] == '$' && argv[i][1] == '?')
		{
			free(argv[i]);
			argv[i] = ft_itoa((*info)->exitstatus);
			(*info)->exitstatus = 0;
		}*/
		i++;
	}
	return (argv);
}

static void	error_max_size(void)
{
	ft_putstr_fd("Expanded string exceeds maximum size\n", 2);
	exit(EXIT_FAILURE);
}

static int	handle_env_var(const char *str, size_t i, 
							char *expanded, size_t *index)
{
	const char	*env_start;
	const char	*env_end;
	const char	*env_value;
	char		*env_name;
	size_t		env_name_len;

	env_start = str + i + 1;
	env_end = env_start;
	while (*env_end && (*env_end == '_' || ft_isalnum(*env_end)))
		env_end++;
	env_name_len = env_end - env_start;
	env_name = (char *)malloc(env_name_len + 1);
	ft_strlcpy(env_name, env_start, env_name_len + 1);
	env_value = getenv(env_name);
	free(env_name);
	if (env_value != NULL)
	{
		if (*index + ft_strlen(env_value) >= PATH_MAX)
			error_max_size();
		ft_strlcpy(expanded + *index, env_value, PATH_MAX - *index);
		*index += ft_strlen(env_value);
		return (env_end - str - 1); // Move to char after env name
	}
	else
		return (env_end - str); // Move to char after env name (if not found)
}

static void	copy_to_expanded(char *expanded, size_t *index, char c)
{
	expanded[*index] = c;
	(*index)++;
	if (*index >= PATH_MAX)
		error_max_size();
}

/* 	Expands env variables $USER, $HOME, etc in quoted strings
	returns a new string with the expanded variables
	note: called by parse_tokens()
	*/
char	*expand_env_in_str(const char *str)
{
	size_t	len;
	char	*expanded;
	size_t	index;
	size_t		i;

	index = 0;
	len = ft_strlen(str);
	expanded = (char *)malloc(PATH_MAX);
	if (expanded == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < len)
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '?')
			i = handle_env_var(str, i, expanded, &index);
		else
			copy_to_expanded(expanded, &index, str[i]);
		i++;
	}
	expanded[index] = '\0';
	return (expanded);
}
