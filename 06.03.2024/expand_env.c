/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:23:46 by zhedlund          #+#    #+#             */
/*   Updated: 2024/01/14 15:53:29 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell_tree.h"

/* 	Expands environment variables in the form of $USER, $HOME, etc. 
	returns a new array with the expanded variables
	note: called by parse_tokens()
	*/

/*char **expand_env(char **argv)
{
    int		i;
	char	*name;
	char	*value;
	
	i = 0;
    while (argv[i] != NULL)
    {
        if (argv[i][0] == '$' && argv[i][1] != '\0')
        {
            name = argv[i] + 1;
            value = getenv(name);
            if (value != NULL)
            {
                free(argv[i]);
                argv[i] = ft_strdup(value);
            }
        }
        i++;
    }
    return (argv);
}*/


// I think it's working! 25.01
// needs to be norminetted big time
// Function to expand environment variables in a string / withon quotes

char *expand_env_in_str(const char *str)
{
    size_t len = strlen(str);
    char *expanded = malloc(len + 1);  // Allocate memory for the expanded string
    if (expanded == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    size_t index = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '?') 
        {
            const char *env_start = str + i + 1;
            const char *env_end = env_start;

            while (*env_end && (*env_end == '_' || ft_isalnum(*env_end)))
                ++env_end;
            size_t env_name_len = env_end - env_start;
            char env_name[env_name_len + 1];
            strncpy(env_name, env_start, env_name_len);
            env_name[env_name_len] = '\0';
            const char *env_value = getenv(env_name);
            if (env_value != NULL) {
                size_t new_len = index + strlen(env_value) + 1;  // Calculate the new length
                expanded = realloc(expanded, new_len);  // Resize the memory
                if (expanded == NULL) {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
                ft_strcat(expanded, env_value);
                index += strlen(env_value);
                i = env_end - str - 1;  // Move to the character after the environment variable name
                continue;
            }
            else {
                // Handle the case where the environment variable doesn't exist
            i = env_end - str;  // Move to the character after the environment variable name
            continue;
            }
        }
        expanded[index++] = str[i];
    }
    expanded[index] = '\0';  // Null-terminate the expanded string
    return expanded;
}
