/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:52:41 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/23 12:52:44 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	ft_exportfree(t_exec *exec_cmd, t_env **head, t_info **info)
{
	int	a;

	a = 0;
	if ((*info)->inchild == true)
	{
		ft_freelist(head);
		free((*info));
		exit(0);
	}
	else
	{
		(*info)->exitstatus = 0;
		while (exec_cmd->argv[a] != NULL)
		{
			free(exec_cmd->argv[a]);
			a++;
		}
		free(exec_cmd);
	}
}

void	ft_invalid_identifier(t_env **head, t_info **info, t_exec *exec_cmd)
{
	ft_putstr_fd("':  not a valid identifier\n", 2);
	(*info)->exitstatus = 1;
	if ((*info)->inchild == true)
	{
		ft_exportfree(exec_cmd, head, info);
		exit(1);
	}
}

int	ft_valididentifier(char *check)
{
	int	a;

	a = 0;
	while (check[a] != '\0')
	{
		if ((check[a] >= 65 && check[a] <= 90)
			|| (check[a] >= 97 && check[a] <= 122))
			a++;
		else
			break ;
	}
	if (check[a] == '=' && a != 0)
		return (0);
	if (check[a] == '\0')
		return (1);
	else
	{
		ft_putstr_fd("Minishell: export: '", 2);
		ft_putstr_fd(check, 2);
		return (2);
	}
}

bool	ft_unexpectedtoken(char *check)
{
	int		a;
	bool	unexpected;

	unexpected = false;
	a = 0;
	while (check[a] != '\0')
	{
		if (check[a] == '(' || check[a] == ')')
			unexpected = true;
		if (unexpected == true)
			break ;
		else
			a++;
	}
	if (unexpected == false)
		return (false);
	ft_putstr_fd("Minishell: syntax error near unexpected token '", 2);
	write(2, &check[a], 1);
	write(2, "'\n", 2);
	return (true);
}

bool	ft_syntax_check(t_exec *exec_cmd, t_env **head, t_info **info)
{
	int		a;
	bool	unexpected;
	char	**check;

	check = exec_cmd->argv;
	unexpected = false;
	a = 1;
	while (check[a] != NULL && unexpected == false)
	{
		unexpected = ft_unexpectedtoken(check[a]);
		if (unexpected == true)
			(*info)->exitstatus = 2;
		a++;
	}
	if (unexpected == false)
		return (unexpected);
	else if ((*info)->inchild == true)
	{
		ft_exportfree(exec_cmd, head, info);
		exit((*info)->exitstatus);
	}
	return (unexpected);
}
