/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:14 by jelliott          #+#    #+#             */
/*   Updated: 2024/01/15 12:14:25 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

/* cmd: pointer to the command struct
	return: void
	note: the function is called by: main()
 */
// Execute cmd.  Never returns.

//this function is to solve the probelm of having env | grep ft - then everything finishes on time and cat is treated differently 
bool ft_forkornottofork(t_exec *exec_cmd)
{
	char	*cmdcopy;
	bool	tofork;

	tofork = true;
	cmdcopy = ft_strdup(exec_cmd->argv[0]);
	if (strncmp(cmdcopy, "cat", ft_strlen(cmdcopy)) == 0)
		tofork = false;
	free(cmdcopy);
	return (tofork);
}

void run_cmd(t_cmd *cmd, t_env **head)
{
	int	pid;
	bool tofork;

	tofork = ft_forkornottofork((t_exec *)cmd);
    if (cmd == 0)
        exit(0);
    if (cmd->type == ' ')
    {
		if (tofork == false)
			handle_exec_cmd((t_exec *)cmd, head);
		else
		{
    		if ((pid = fork()) == 0)
        		handle_exec_cmd((t_exec *)cmd, head);
    		wait(&pid);
    	}
	}
	else if (cmd->type == '>' || cmd->type == '<' || cmd->type == 'x' || cmd->type == 'h') //this will have to be altered
        handle_redir_cmd((t_redir *)cmd, head);
    else if (cmd->type == '|')
    {
    	if ((pid = fork()) == 0)
        	handle_pipe_cmd((t_pipe *)cmd, head);
    	wait(&pid);
    }
    else
	{
        ft_putstr_fd("unknown run_cmd\n", 2);
        exit(-1);
    }
	ft_freelist(head);
    exit(0);
}

void	ft_ctrlc2(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		//printf("SIGINCAT\n");
		rl_replace_line("\0", 0);
		write(STDERR_FILENO, "\n", 1);
		//rl_on_new_line();
		rl_redisplay();
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
        	write(1, "\033[K", 3); //"\033[K" is an escape code that means clear the line (it prevents a ghostly ^\ from appearing)
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

/* buf: pointer to the buffer to store the input
	nbuf: size of the buffer
	return: 0 if input is not empty, -1 otherwise
	note: the function is called by: main()
 */
 // ctrl\ ctrlc now taken care of
int get_cmd(char *buf, int nbuf, t_env **head)
{
	char	*input;
	
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, ft_ctrlc);
	if (isatty(0)) // checks if connected to stdin (fd 0)
		input = readline("minishell> "); // read input w promt - interactive mode
	else
		input = readline(""); // read input w/o promt - non-interactive mode
	// Handle EOF or empty input (also takes care of ctrld)
	//have removed if == 0 - because then pressing enter exits
	//have added exit here - if it is run in pipes then nothing happens - that can be reflecetd later in the code
	if (input == NULL || ft_strlen(input) == 4 
		&& ft_strncmp("exit", input, 4) == 0)
	{
		if (input != NULL)
			free(input); // free memory allocated by readline()
		//killpg(getpgrp(), SIGKILL); //suspect this isn't allowed, but experimenting
		return (-1);
	}
	//printf("input == %s\n", input);
	//printf("buf == %s\n", buf);
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
