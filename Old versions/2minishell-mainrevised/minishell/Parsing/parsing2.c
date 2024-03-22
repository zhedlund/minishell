/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:08:48 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/19 15:58:05 by zhedlund         ###   ########.fr       */
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
t_cmd *parse_redir(t_cmd *cmd, char **position_ptr, char *end_str, t_info **info)
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
			cmd = redir_cmd(cmd, make_copy(file_start, file_end), '<', info);
		else if (redir_type == '>')
            cmd = redir_cmd(cmd, make_copy(file_start, file_end), '>', info);
		else if (redir_type == 'x')
			cmd = redir_cmd(cmd, make_copy(file_start, file_end), 'x', info);
		else if (redir_type == 'h')
			cmd = redir_cmd(cmd, make_copy(file_start, file_end), 'h', info);
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
void parse_tokens(t_exec *exec_cmd, t_cmd **cmd, char **position_ptr, char *end_str, t_info **info)
{
    int		args;
    char	*token_start;
    char	*token_end;
    int		token_type;
	char	*expanded_token;

	args = 0;
	while (!check_next_token(position_ptr, end_str, "|"))
	{
		token_type = get_token(position_ptr, end_str, &token_start, &token_end);
		if (token_type == 0)
			break;
		if (token_type == 'q' || token_type == 'd')
		{
			exec_cmd->argv[args] = make_copy(token_start, token_end - 1); // Exclude the ending quote
			printf("token qd: %s\n", exec_cmd->argv[args]); //debug statement
		}
		else
			exec_cmd->argv[args] = make_copy(token_start, token_end);
		if (token_type != 'q')
		{
    		printf("token ad1: %s\n", exec_cmd->argv[args]); //debug statement
			printf("info exitpre expand: %d\n", (*info)->exitstatus); //debug statement
			expand_env(&exec_cmd->argv[args], info); // Expand environment variables
    		expanded_token = expand_env_in_str(exec_cmd->argv[args]); // Expand environment variables within double-quoted strings
    		printf("token ad2: %s\n", expanded_token); // debug statement
    		free(exec_cmd->argv[args]); // Free the original token
    		exec_cmd->argv[args] = expanded_token; // Assign the expanded token
		}
		args++;
		if (args >= MAXARGS)
			ft_putstr_fd("Too many arguments\n", 2);
		*cmd = parse_redir(*cmd, position_ptr, end_str, info);
	}
	exec_cmd->argv[args] = NULL;
}

/* 	
	Function to parse execution commands
	position_ptr: pointer to the pointer to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: parse_pipe()
*/
t_cmd *parse_exec(char **position_ptr, char *end_str, t_info **info)
{
    t_cmd *cmd;
    t_exec *exec_command;

	cmd = exec_cmd();
	exec_command = (t_exec *)cmd;
    cmd = parse_redir(cmd, position_ptr, end_str, info);
    parse_tokens(exec_command, &cmd, position_ptr, end_str, info);
    return (cmd);
}
