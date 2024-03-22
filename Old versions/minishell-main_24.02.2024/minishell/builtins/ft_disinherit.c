/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_disinherit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:10:00 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/22 21:11:13 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

void	get_env(t_env **head)
{
	extern char	**environ;
	int			i;
	t_env		*temp;
	t_env		*node;

	i = 1;
	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		perror("malloc");
	node->field = ft_strdup(environ[0]);
	*head = node;
	while (environ[i] != NULL)
	{
		temp = (t_env *)malloc(sizeof(t_env));
		if (!temp)
			exit (1);
		temp->field = ft_strdup(environ[i]);
		node->next = temp;
		temp->prev = node;
		node = temp;
		node->next = NULL;
		i++;
	}
	temp = *head;
	temp->prev = node->next;
}

/* decides whether to block or unblock non-builtin simple functions
 * on the basis of whether or not PATH has been unset, or reset properly
 * alter bool in info array that is checked by later functions
 * info: pointer to the info struct
 * cmdarray: array of strings containing the command and its arguments
 * return: void
 * note: this function is called by: main()
*/

void	ft_unsetpath(t_info **info, char **cmdarray)
{
	extern char	**environ;
	int			find;

	find = 0;
	while (ft_strncmp(environ[find], "PATH=", 4) != 0)
		find++;
	if (ft_identical(cmdarray[0], "unset") == true
		&& cmdarray[1] != NULL 
		&& ft_identical(cmdarray[1], "PATH") == true)
		(*info)->unsetpath = true;
	if (ft_identical(cmdarray[0], "export") == true
		&& (ft_strlen(cmdarray[1]) >= ft_strlen("PATH"))
		&& (ft_strncmp(cmdarray[1], "PATH", ft_strlen("PATH")) == 0))
	{
		if (ft_strlen(cmdarray[1]) != ft_strlen(environ[find]))
			(*info)->unsetpath = true;
		else if (ft_identical(cmdarray[0], "export") == true
			&& cmdarray[1] != NULL 
			&& ft_identical(environ[find], cmdarray[1]) == true)
			(*info)->unsetpath = false;
	}
}

int	ft_disinherit(char *buf, t_env **head, t_info **info)
{
	int		a;
	char	**cmdarray;

	a = 0;
	while (buf[a] != '\0')
	{
		if (buf[a] == '|' || buf[a] == '<' || buf[a] == '>')
			return (false);
		a++;
	}
	cmdarray = ft_split(buf, ' ');
	if (ft_identical("export", cmdarray[0]) == true
		|| ft_identical("unset", cmdarray[0]) == true
		|| ft_identical("cd", cmdarray[0]) == true
		|| ft_identical("exit", cmdarray[0]) == true)
	{
		if (ft_identical("exit", cmdarray[0]) == true)
			ft_freearray(cmdarray);
		run_cmd(parse_cmd(buf, info, head), head, info);
		ft_unsetpath(info, cmdarray);
		ft_freearray(cmdarray);
		return (true);
	}
	ft_freearray(cmdarray);
	return (false);
}
