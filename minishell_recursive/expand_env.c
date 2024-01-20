/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:23:46 by zhedlund          #+#    #+#             */
/*   Updated: 2024/01/20 17:59:22 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tree.h"

/* 	Expands environment variables in the form of $USER, $HOME, etc. 
	returns a new array with the expanded variables
	note: called by parse_tokens()
	*/

char **expand_env(char **argv)
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
}

// Function to expand environment variables within double-quoted strings
void expand_env_in_quotes(char *str)
{
    char *start = str;
    char *expanded = malloc(strlen(str) + 1); // Allocate memory for the expanded string
    char *dest = expanded;

    while (*str)
    {
        if (*str == '$' && *(str + 1) != '\0') // Check for $VAR format
        {
            char *env_start = str + 1; // Point to the beginning of the environment variable name
            // Find the end of the environment variable name
            char *env_end = env_start;
            while (*env_end && (*env_end == '_' || (*env_end >= 'A' && *env_end <= 'Z') || (*env_end >= 'a' && *env_end <= 'z') || (*env_end >= '0' && *env_end <= '9')))
                env_end++;
            // Extract the environment variable name
            size_t env_name_len = env_end - env_start;
            char env_name[env_name_len + 1];
            ft_strlcpy(env_name, env_start, sizeof(env_name)); // Use strlcpy
            env_name[env_name_len] = '\0';
            // Lookup the environment variable value
            char *env_value = getenv(env_name);
            if (env_value != NULL)
            {
                // Append the environment variable value to the expanded string
                while (*env_value)
                    *dest++ = *env_value++;
                str = env_end; // Move to the character after the environment variable name
                continue;
            }
        }
        // Copy the character as is
        *dest++ = *str++;
    }
    *dest = '\0'; // Null-terminate the expanded string
    ft_strcpy(start, expanded); // Update the original string with the expanded version
    free(expanded); // Free the dynamically allocated memory
}


/*int main(void)
{
    char str[] = "hello $USER, welcome to $HOME/minishell";
    printf("Before: %s\n", str);
    expand_env_in_quotes(str);
    printf("After: %s\n", str);
    return 0;
}*/
