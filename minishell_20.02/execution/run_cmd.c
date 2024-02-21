/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsinitial.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:14 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/20 21:06:57 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

/* cmd: pointer to the command struct
	return: void
	note: the function is called by: main()
 */
// Execute cmd.  Never returns.

void run_cmd(t_cmd *cmd, t_env **head, t_info **info)
{
    if (cmd == 0)
        exit(0);
    if (cmd->type == ' ')
			handle_exec_cmd((t_exec *)cmd, head, info);
	else if (cmd->type == '>' || cmd->type == '<' || cmd->type == 'x' || cmd->type == 'h') //this will have to be altered
        handle_redir_cmd((t_redir *)cmd, head, info);
   else if (cmd->type == '|')
    {
		(*info)->inchild = true;
		handle_pipe_cmd((t_pipe *)cmd, head, info);
	}
	else
	{
        ft_putstr_fd("unknown run_cmd\n", 2);
        exit(-1);
    }
}