/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:08:48 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/15 12:08:49 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

/* cmd: pointer to the command struct
	position_ptr: pointer to the pointer to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: parse_exec(), parse_redir(), parse_pipe(), parse_cmd(),
	run_cmd(), main(), get_cmd()
 */
t_cmd *parse_redir(t_cmd *cmd, char **position_ptr, char *end_str)
{
    int		redir_type;
    char	*file_start;
	char	*file_end;

    while (check_next_token(position_ptr, end_str, "<>"))
	{
        redir_type = get_token(position_ptr, end_str, 0, 0);
        if (get_token(position_ptr, end_str, &file_start, &file_end) != 'a')
		{
            ft_putstr_fd("missing file for redirection\n", 2);
            exit(-1);
        }
        if (redir_type == '<')
			cmd = redir_cmd(cmd, make_copy(file_start, file_end), '<');
		else if (redir_type == '>')
            cmd = redir_cmd(cmd, make_copy(file_start, file_end), '>');
		else if (redir_type == 'x')
			cmd = redir_cmd(cmd, make_copy(file_start, file_end), 'x');
		//else if (redir_type == 'h')
			//cmd = redir_cmd(cmd, make_copy(file_start, file_end), 'h');
        //else - handle unexpected token here if needed / print an error message)
    }
    return (cmd);
}

/* Function to handle token parsing and filling arguments
	exec_cmd: pointer to the command struct
	cmd: pointer to the pointer to the command struct
	position_ptr: pointer to the pointer to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	note: the function is called by: parse_exec()
*/

/* Function to parse tokens and fill arguments with environmental variable expansion */
void parse_tokens(t_exec *exec_cmd, t_cmd **cmd, char **position_ptr, char *end_str)
{
    int args = 0;
    char *token_start;
    char *token_end;
    int token_type;
	char **expanded_arg;

    while (!check_next_token(position_ptr, end_str, "|"))
    {
        token_type = get_token(position_ptr, end_str, &token_start, &token_end);
        if (token_type == 0)
            break;
        exec_cmd->argv[args] = make_copy(token_start, token_end);
        args++;
        if (args >= MAXARGS)
        {
            ft_putstr_fd("too many args\n", 2);
            exit(-1);
        }
        *cmd = parse_redir(*cmd, position_ptr, end_str);
    }
    exec_cmd->argv[args] = NULL;
    expanded_arg = expand_env(exec_cmd->argv);
}

/* 	
	Function to parse execution commands
	position_ptr: pointer to the pointer to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: parse_pipe()
*/
t_cmd *parse_exec(char **position_ptr, char *end_str)
{
    t_cmd *cmd;
    t_exec *exec_command;

	cmd = exec_cmd();
	exec_command = (t_exec *)cmd;
    cmd = parse_redir(cmd, position_ptr, end_str);
    parse_tokens(exec_command, &cmd, position_ptr, end_str);
    return (cmd);
}
