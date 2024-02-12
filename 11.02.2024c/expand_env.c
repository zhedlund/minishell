/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:23:46 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/12 22:32:10 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tree.h"

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
		if (argv[i][0] == '$' && argv[i][1] == '?')
		{
			free(argv[i]);
			argv[i] = ft_itoa((*info)->exit_status);
		}
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

static void	copy_char_to_expanded(char *expanded, size_t *index, char c)
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
	int		i;

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
			copy_char_to_expanded(expanded, &index, str[i]);
		i++;
	}
	expanded[index] = '\0';
	return (expanded);
}
