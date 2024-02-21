/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtinsmenu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:10:00 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/21 16:07:50 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

void	ft_builtinsmenu(char *argv, char **cmdinfo, t_env **head, t_info **info)
{
	(*info)->inchild = false;
	if (ft_strlen("cd") == ft_strlen(argv) 
		&& ft_strncmp(argv, "cd", ft_strlen(argv)) == 0)
		ft_cd(cmdinfo, head, info);
	else if (ft_strlen("unset") == ft_strlen(argv) 
		&& ft_strncmp(argv, "unset", ft_strlen(argv)) == 0)
		ft_unset(argv, cmdinfo, head, info);
	else if (ft_strlen("exit") == ft_strlen(argv) 
		&& ft_strncmp(argv, "exit", ft_strlen(argv)) == 0)
		ft_exit(cmdinfo, head, info);
	else if (ft_strlen("export") == ft_strlen(argv) 
		&& ft_strncmp(argv, "export", ft_strlen(argv)) == 0)
		ft_export(cmdinfo, head, info);
	else if(argv != NULL)
	{
		write(2, "Command not found: ", ft_strlen("Command not found: ")); 
		write(2, argv, ft_strlen(argv));
		write(2, "\n", ft_strlen("\n"));
		ft_freelist(head);
		ft_freearray(cmdinfo);
		free(*info);
		exit(127);
	}
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
	int	find;

	find = 0;
	while (ft_strncmp(environ[find], "PATH=", 4) != 0)
		find++;
	if (ft_strncmp(cmdarray[0], "unset", ft_strlen(cmdarray[0])) == 0
				&& cmdarray[1] != NULL 
					&& ft_strncmp(cmdarray[1], "PATH", ft_strlen(cmdarray[1])) == 0)
				(*info)->unsetpath = true;
	if (ft_strncmp(cmdarray[0], "export", ft_strlen(cmdarray[0])) == 0
				&& (ft_strlen(cmdarray[1]) >= ft_strlen("PATH"))
					&& (ft_strncmp(cmdarray[1], "PATH", ft_strlen("PATH")) == 0))
	{
		if (ft_strlen(cmdarray[1]) != ft_strlen(environ[find]))
			(*info)->unsetpath = true;
		else if (ft_strncmp(cmdarray[0], "export", ft_strlen(cmdarray[0])) == 0
				&& cmdarray[1] != NULL 
					&& ft_strncmp(environ[find], cmdarray[1], ft_strlen(cmdarray[1])) == 0)
				(*info)->unsetpath = false;
	}
}

//this function 'disinherits' the child process by altering the environment that it inherits
//this is important because environment altering functions don't affect the parent process
//so send 'unset' to the child process and it will unset only the child process's copy of the environmental variables
//that means if you subsequently enter env, then the program will print out the parent's envs which still include the unset variable
int	ft_disinherit(char *buf, t_env **head, t_info **info)
{
	int a;
	char **cmdarray;

	a = 0;
	while (buf[a] != '\0')
	{
		if(buf[a] == '|' || buf[a] == '<' || buf[a] == '>')
			return (false);
		a++;
	}
	cmdarray = ft_split(buf, ' ');
	if ((ft_strlen(cmdarray[0]) == ft_strlen("export")
		 && ft_strncmp(cmdarray[0], "export", ft_strlen(buf)) == 0)
			|| (ft_strlen(cmdarray[0]) == ft_strlen("unset")
				&& ft_strncmp(cmdarray[0], "unset", ft_strlen(buf)) == 0))
	{
			run_cmd(parse_cmd(buf, info, head), head, info);
			ft_unsetpath(info, cmdarray);
			ft_freearray(cmdarray);
			return (true);
	}
	if ((ft_strlen(cmdarray[0]) == ft_strlen("cd") 
			&& ft_strncmp(cmdarray[0], "cd", ft_strlen(buf)) == 0)
				|| (ft_strlen(cmdarray[0]) == ft_strlen("exit")
					&& ft_strncmp(cmdarray[0], "exit", ft_strlen(buf)) == 0))
	{
			if (ft_strlen(cmdarray[0]) == ft_strlen("exit"))
				ft_freearray(cmdarray);
			run_cmd(parse_cmd(buf, info, head), head, info);
			ft_freearray(cmdarray);
			return (true);
	}
	printf("here!\n");
	ft_freearray(cmdarray);
	return (false);
}


