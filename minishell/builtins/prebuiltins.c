/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prebuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:59:55 by jelliott          #+#    #+#             */
/*   Updated: 2024/03/26 18:20:43 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_is_there_a_path_sub(char **path_options, char *hold)
{
	int		a;
	char	*poss;

	a = 0;
	while (path_options[a] != NULL)
	{
		poss = ft_strjoin(path_options[a], hold);
		if (access(poss, X_OK) == 0)
		{
			free (poss);
			break ;
		}
		free(poss);
		a++;
	}
	return (path_options[a]);
}

bool	ft_path_search_sub(char *temp, t_exec *exec_cmd, char *hold,
								char *path_options_prep)
{
	char	**path_options;
	int		a;
	bool	path;
	char	*copy;

	a = 0;
	path = true;
	hold = ft_strjoin("/", exec_cmd->argv[0]);
	path_options_prep = ft_strtrim(temp, "PATH=");
	path_options = ft_split(path_options_prep, ':');
	copy = hold;
	hold = ft_is_there_a_path_sub(path_options, copy);
	if (path_options[a] == NULL)
		path = false;
	free(path_options_prep);
	free(copy);
	ft_freearray(path_options);
	return (path);
}

void	ft_is_there_a_path(char *temp, t_exec *exec_cmd, t_info **info, 
							t_env **head)
{
	bool	path;
	char	*hold;
	char	*p_o_p;

	hold = NULL;
	p_o_p = NULL;
	path = true;
	if (exec_cmd->argv[0] != NULL 
		&& exec_cmd->argv[0][0] != '\0')
	{
		ft_path_search_sub(temp, exec_cmd, hold, p_o_p);
		if (path == false)
		{
			ft_putstr_fd("The command could not be located, ", 2);
			ft_putstr_fd("please alter the PATH environmental variable\n", 2);
			ft_multifree(head, info, exec_cmd);
			exit (127);
		}
	}
}

void	ft_tempisnull(t_exec *exec_cmd, t_info **info, t_env **head)
{
	ft_putstr_fd("Minishell: ", 2); 
	ft_putstr_fd(exec_cmd->argv[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	(*info)->unsetpath = true;
	(*info)->exitstatus = 127;
	if ((*info)->exiting == true)
	{
		rl_clear_history();
		ft_multifree(head, info, exec_cmd);
		exit (127);
	}
}

void	ft_pathexperiment(t_exec *exec_cmd, t_info **info, t_env **head)
{
	t_env	*temp;
	char	*copy;

	temp = *head;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->field, "PATH", ft_strlen("PATH")) == 0)
			break ;
		else
			temp = temp->next;
	}
	if (temp == NULL)
		ft_tempisnull(exec_cmd, info, head);
	else
	{
		copy = ft_strdup(temp->field);
		ft_is_there_a_path(copy, exec_cmd, info, head);
		free(copy);
	}
	if (ft_identical(exec_cmd->argv[0], "env") == true)
		ft_env(head, info, exec_cmd);
	else if ((*info)->unsetpath == false)
		ft_execvp(exec_cmd, exec_cmd->argv, head, info);
}
