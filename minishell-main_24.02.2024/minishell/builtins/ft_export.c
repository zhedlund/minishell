/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:28:33 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/23 12:36:00 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

bool	ft_equalpresent(char *check)
{
	bool		validcheck;
	int			a;

	a = 0;
	validcheck = false;
	while (check[a] != '\0')
	{
		if (check[a] == '=')
			validcheck = true;
		a++;
	}
	return (validcheck);
}

void	ft_exportsub(char *toexport, t_env **head)
{
	t_env	*holdnext;
	t_env	*hold;
	t_env	*insert;
	char	**split;

	split = ft_split(toexport, '=');
	ft_unsetsub(split[0], head);
	ft_freearray(split);
	hold = *head;
	holdnext = (*head)->next;
	insert = (t_env *)malloc(sizeof(t_env));
	insert->field = ft_strdup(toexport);
	(*head)->next = insert;
	insert->prev = *head;
	insert->next = holdnext;
	holdnext->prev = insert;
}

void	ft_solo_export(t_env **head, t_info **info, t_exec *exec_cmd)
{
	t_env	*temp;

	temp = *head;
	while (temp != NULL)
	{
		printf("declare -x %s\n", temp->field);
		temp = temp->next;
	}
	(*info)->exitstatus = 0;
	if ((*info)->inchild == true)
	{
		ft_exportfree(exec_cmd, head, info);
		exit(0);
	}
}

void	valid_identifier_export(t_exec *exec_cmd, t_env **head, t_info **info)
{
	int		a;
	int		export;
	char	**check;

	check = exec_cmd->argv;
	a = 1;
	export = 0;
	while (check[a] != NULL)
	{
		export = ft_valididentifier(check[a]);
		if (export == 2)
			ft_invalid_identifier(head, info, exec_cmd);
		if (ft_equalpresent(check[a]) == true && export != 2)
		{
			ft_exportsub(check[a], head);
			(*info)->exitstatus = 0;
		}
		a++;
	}
}

//initial check if simply 'export' and prints accordingly
//next, checks for unexpected token syntax error
//if none of the above, simultaneously checks for syntax errors, presence of '='
//and exports if none 
//(this allows for a command line that has some exports and some errors)
//note, the export function both adds variables if not on the env list
//and alters variables if they are on the env list
void	ft_export(t_exec *exec_cmd, t_env **head, t_info **info)
{
	char	**check;
	bool	unexpected;
	t_env	*temp;

	temp = *head;
	unexpected = false;
	check = exec_cmd->argv;
	if (check[1] == NULL)
		ft_solo_export(head, info, exec_cmd);
	else
	{
		unexpected = ft_syntax_check(exec_cmd, head, info);
		if (unexpected == false)
			valid_identifier_export(exec_cmd, head, info);
	}
	ft_exportfree(exec_cmd, head, info);
}
