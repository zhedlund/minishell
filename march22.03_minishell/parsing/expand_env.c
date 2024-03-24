/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:38:58 by zhedlund          #+#    #+#             */
/*   Updated: 2024/03/22 15:24:12 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_env_var(const char *str, char *expanded, 
							size_t *index, t_env **head)
{
	const char	*start;
	const char	*end;
	const char	*value;
	char		*name;
	size_t		len;

	start = str + (*head)->i + 1;
	end = start;
	while (*end && (*end == '_' || ft_isalnum(*end)))
		end++;
	len = end - start;
	name = (char *)malloc(sizeof(len + 1));
	ft_strlcpy(name, start, len + 1);
	value = ft_findvalue(name, head);
	free(name);
	if (value != NULL)
	{
		if (*index + ft_strlen(value) >= PATH_MAX)
			error_max_size();
		ft_strlcpy(expanded + *index, value, PATH_MAX - *index);
		*index += ft_strlen(value);
		return (end - str - 1);
	}
	else
		return (end - str);
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
char	*expand_env_in_str(const char *str, int exit_status, t_env **head)
{
	char	*expanded;
	size_t	index;

	index = 0;
	expanded = (char *)malloc(PATH_MAX);
	if (!expanded)
		return (NULL);
	(*head)->i = 0;
	while ((*head)->i < ft_strlen(str))
	{
		if (str[(*head)->i] == '$' && str[(*head)->i + 1] != '\0' && str[(*head)->i + 1] != '?')
			(*head)->i = handle_env_var(str, expanded, &index, head);
		else if (str[(*head)->i] == '$' && str[(*head)->i + 1] == '?')
		{
			expand_exit_status(exit_status, expanded, &index);
			(*head)->i++;
		}
		else
			copy_to_expanded(expanded, &index, str[(*head)->i]);
		(*head)->i++;
	}
	expanded[index] = '\0';
	return (expanded);
}

/* 	Expands environment variables in the form of $USER, $HOME, etc. 
	returns a new array with the expanded variable
	note: called by parse_tokens()
	*/
char	**expand_env(char **argv, t_env **head)
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
			value = ft_findvalue(name, head);
			free(argv[i]);
			if (value != NULL)
				argv[i] = ft_strdup(value);
		}
		i++;
	}
	return (argv);
}

void	expand_env_var(t_exec *cmd, int args, t_info **info, t_env **head)
{
	char	*token;

	//expand_env(&cmd->argv[args], head);
	token = expand_env_in_str(cmd->argv[args], (*info)->exitstatus, head);
	free(cmd->argv[args]);
	cmd->argv[args] = token;
}
