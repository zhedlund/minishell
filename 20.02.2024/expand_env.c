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
	note: the original array is freed
	note: the new array must be freed by the caller
	note: called by parse_tokens()
	*/

char **expand_env(char **argv)
{
    int i;
	char *name;
	char *value;
	
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
