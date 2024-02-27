/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:38:58 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/23 17:28:58 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_env_var(const char *str, size_t i, 
							size_t *index, t_env **head)
{
	const char	*env_start;
	const char	*env_end;
	const char	*env_value;
	char		*env_name;
	size_t		len;

	env_start = str + i + 1;
	env_end = env_start;
	while (*env_end && (*env_end == '_' || ft_isalnum(*env_end)))
		env_end++;
	len = env_end - env_start;
	env_name = (char *)malloc(sizeof(len + 1));
	ft_strlcpy(env_name, env_start, len + 1);
	env_value = ft_findvalue(env_name, head);
	free(env_name);
	if (env_value != NULL)
	{
		if (*index + ft_strlen(env_value) >= PATH_MAX)
			error_max_size();
		ft_strlcpy((*head)->expanded + *index, env_value, PATH_MAX - *index);
		*index += ft_strlen(env_value);
		return (env_end - str - 1);
	}
	else
		return (env_end - str);
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
	size_t	len;
	size_t	index;
	size_t	i;

	index = 0;
	len = ft_strlen(str);
	(*head)->expanded = (char *)malloc(PATH_MAX);
	if ((*head)->expanded == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < len)
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '?')
			i = handle_env_var(str, i, &index, head);
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			expand_exit_status(exit_status, (*head)->expanded, &index);
			i++;
		}
		else
			copy_to_expanded((*head)->expanded, &index, str[i]);
		i++;
	}
	(*head)->expanded[index] = '\0';
	return ((*head)->expanded);
}

char	*ft_namecut(char *totrim)
{
	int		a;
	int		length;
	char	*trimmed;
	int		b;

	b = 0;
	a = 0;
	length = ft_strlen(totrim);
	while (totrim[a] != '=')
		a++;
	a++;
	trimmed = malloc(sizeof(char) * ((length - a) + 1));
	while (totrim[a] != '\0')
	{
		trimmed[b] = totrim[a];
		a++;
		b++;
	}
	trimmed[b] = '\0';
	return (trimmed);
}

char	*ft_findvalue(char *name, t_env **head)
{
	t_env	*temp;
	char	*minusname;
	int		a;
	char	**split;

	a = ft_strlen(name);
	minusname = NULL;
	temp = *head;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->field, name, a) == 0)
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		return (ft_strdup("\0"));
	split = ft_split(temp->field, '=');
	if (ft_identical(split[0], name) == true)
		minusname = ft_namecut(temp->field);
	ft_freearray(split);
	return (minusname);
}

char	*ft_decidevalue(char *name, t_env **head)
{
	char	*value;
	char	*try;

	if (name[0] >= 48 && name[0] <= 57)
	{
		try = &name[1];
		value = ft_strdup(try);
	}
	else 
		value = ft_findvalue(name, head);
	return (value);
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
			value = ft_decidevalue(name, head);
			if (value != NULL)
			{
				free(argv[i]);
				argv[i] = value;
			}
		}
		i++;
	}
	return (argv);
}
