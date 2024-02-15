/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsinitial.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:14 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/15 17:57:51 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

/* cmd: pointer to the command struct
	return: void
	note: the function is called by: main()
 */
// Execute cmd.  Never returns.
int	globalsignum = 0;
//this function is to solve the probelm of having env | grep ft - then everything finishes on time and cat is treated differently 

bool ft_forkornottofork(t_exec *exec_cmd)
{
	char	*cmdcopy;
	bool	tofork;

	tofork = true;
	cmdcopy = ft_strdup(exec_cmd->argv[0]);
	//printf("exec_cmd->argv[1] == %s\n", exec_cmd->argv[1]);
	if (ft_strncmp(cmdcopy, "cat", ft_strlen(cmdcopy)) == 0)
		tofork = false;
	free(cmdcopy);
	return (tofork);
}

void run_cmd(t_cmd *cmd, t_env **head, t_info **info)
{
	//pid_t	pid;
	bool	tofork;
	int		status;
	
	//tofork = ft_forkornottofork((t_exec *)cmd);
    if (cmd == 0)
        exit(0);
    if (cmd->type == ' ')
    {
		//if (tofork == false)
		handle_exec_cmd((t_exec *)cmd, head, info);
		/*else
		{
    		if ((pid = fork()) == 0)
        		handle_exec_cmd((t_exec *)cmd, head, info);
    		waitpid(pid, &status, 0);
    	}*/
	}
	else if (cmd->type == '>' || cmd->type == '<' || cmd->type == 'x' || cmd->type == 'h') //this will have to be altered
        handle_redir_cmd((t_redir *)cmd, head, info);
    else if (cmd->type == '|')
    {
    	//if ((pid = fork()) == 0)
        handle_pipe_cmd((t_pipe *)cmd, head, info);
    	//waitpid(pid, &status, 0);
    }
    else
	{
        ft_putstr_fd("unknown run_cmd\n", 2);
        exit(-1);
    }
	ft_freelist(head);
    exit(0);
}

/*void run_cmd(t_cmd *cmd, t_env **head, t_info **info)
{
    if (cmd == 0)
        exit(0);
    if (cmd->type == ' ')
        handle_exec_cmd((t_exec *)cmd, head, info);
    else if (cmd->type == '>' || cmd->type == '<' || cmd->type == 'x')
        handle_redir_cmd((t_redir *)cmd, head, info);
    else if (cmd->type == '|')
        handle_pipe_cmd((t_pipe *)cmd, head, info);
    else
	{
        //ft_putstr_fd("unknown run_cmd\n", 2);
		perror("run_cmd");
        exit(1);
    }
    exit(0);
}*/


void	ft_ctrlc2(int signal)
{
	//printf("ctrlc2\n");
	if (signal == SIGINT)
	{
		(void)signal;
		rl_replace_line("\0", 0);
		//write(STDERR_FILENO, "\n", 1);
		//rl_redisplay();
		globalsignum = 4;
	}
	if (signal == SIGQUIT)
	{
		(void)signal;
        	write(1, "\033[K", 3); //"\033[K" is an escape code that means clear the line (it prevents a ghostly ^\ from appearing)
			globalsignum = 2;
			//rl_on_new_line();
    }
}

/* Ctrl-c handle */

void	ft_ctrlc(int sig)
{
	if (sig == SIGQUIT)
	{
		(void)sig;
    		rl_on_new_line();
        	rl_redisplay();
			//printf("ft_ctrlc\n");
        	write(1, "\033[K", 3); //"\033[K" is an escape code that means clear the line (it prevents a ghostly ^\ from appearing)
			rl_redisplay();
    	}
	if (sig == SIGINT)
	{
		(void)sig;
		rl_replace_line("\0", 0);
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	//write(STDERR_FILENO, "\n", 1);
}

/*bool	ft_allcat(char *buf)
{
	char	**check;
	int	i;
	bool	allcat;

	if (buf == NULL)
		return (false);
	allcat = true;
	i = 0;
	check = ft_split(buf, '|');
	printf("%s\n", buf);
	while (check[i] != NULL)
	{
		if(ft_strlen(check[i]) < 2)
		{
			printf("too short\n");	
			allcat = false;
		}
		else if (ft_strncmp(check[i], "cat", 2) != 0)
		{
			printf("not cat\n");
			allcat = false;
		}
		i++;
	}
	return (allcat);
}*/

/* buf: pointer to the buffer to store the input
	nbuf: size of the buffer
	return: 0 if input is not empty, -1 otherwise
	note: the function is called by: main()
 */
 // ctrl\ ctrlc now taken care of
int get_cmd(char *buf, int nbuf, t_env **head)
{
	char	*input;
	//bool	allcat;
	//allcat = ft_allcat(buf);
	signal(SIGINT, ft_ctrlc);
	//if (allcat == false)
	signal(SIGQUIT, ft_ctrlc);
	if (globalsignum != 0)
	{
		if (globalsignum == 2)
			printf("Quit (core dumped)\n");
		if (globalsignum == 4)
			printf("\n");
		globalsignum = 0;
	}
	if (isatty(0)) // checks if connected to stdin (fd 0)
		input = readline("minishell> "); // read input w promt - interactive mode
	else
		input = readline(""); // read input w/o promt - non-interactive mode
	//below is for ctrl-d
	if (input == NULL)
	{
		printf("exit\n");
		exit(130);
	}
	ft_strlcpy(buf, input, nbuf); // copy input to buf
	buf[nbuf - 1] = '\0'; // null-terminated string
    add_history(buf); // Add input to history
    free(input); // Free memory allocated by readline()
	return (0);
}

/* 	return: pid of the child process
	note: the function is called by: run_cmd()
 */
// Fork but perror on failure
int fork_process(void)
{
	int pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}
