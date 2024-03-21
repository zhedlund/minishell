/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:20:04 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/15 12:20:07 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

/* Execution */

/* exec_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void handle_exec_cmd(t_exec *exec_cmd, t_env **head)
{
    if (exec_cmd->argv[0] == 0)
        exit(0);
    ft_execvp(exec_cmd->argv[0], exec_cmd->argv, head);
}
