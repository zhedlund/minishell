/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:23:46 by zhedlund          #+#    #+#             */
/*   Updated: 2024/01/13 19:41:36 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tree.h"

/* 	Expands environment variables in the form of $USER, $HOME, etc. 
	returns a new array with the expanded variables */

char **expand_env(char **argv)
{
    int i = 0;
	char *name;
	char *value;
	
    while (argv[i] != NULL)
    {
        if (argv[i][0] == '$' && argv[i][1] != '\0')
        {
            name = argv[i] + 1;
            value = getenv(name);
            if (value != NULL)
            {
                free(argv[i]);
                argv[i] = strdup(value);
            }
        }
        i++;
    }
    return (argv);
}
