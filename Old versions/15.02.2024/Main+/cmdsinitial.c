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

void run_cmd(t_cmd *cmd, t_env **head, t_info **info)
{
	int	pid;
	bool tofork;
	
	//tofork = ft_forkornottofork((t_exec *)cmd);
	(*info)->inchild = true;
    if (cmd == 0)
        exit(0);
    if (cmd->type == ' ')
			handle_exec_cmd((t_exec *)cmd, head, info);
	else if (cmd->type == '>' || cmd->type == '<' || cmd->type == 'x' || cmd->type == 'h') //this will have to be altered
        handle_redir_cmd((t_redir *)cmd, head, info);
   else if (cmd->type == '|')
        	handle_pipe_cmd((t_pipe *)cmd, head, info);
    else
	{
        ft_putstr_fd("unknown run_cmd\n", 2);
        exit(-1);
    }
	//ft_freelist(head);
    //exit(0);
}

void	ft_ctrlc2(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		rl_replace_line("\0", 0);
		g_signal = 4;
	}
	if (signal == SIGQUIT)
	{
		(void)signal;
        	write(1, "\033[K", 3); //"\033[K" is an escape code that means clear the line (it prevents a ghostly ^\ from appearing)
			g_signal = 2;
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
}

/* buf: pointer to the buffer to store the input
	nbuf: size of the buffer
	return: 0 if input is not empty, -1 otherwise
	note: the function is called by: main()
 */
 // ctrl\ ctrlc now taken care of
int get_cmd(char *buf, int nbuf, t_env **head, t_info **info)
{
	char	*input;

	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, ft_ctrlc);
	if (g_signal != 0)
	{
		if (g_signal == 2 && (*info)->allcat == true)
			printf("Quit (core dumped)\n");
		if (g_signal == 4)
			printf("\n");
		g_signal = 0;
		//(*info)->exitstatus = 131;
	}
	if (isatty(0)) // checks if connected to stdin (fd 0)
		input = readline("minishell> "); // read input w promt - interactive mode
	else
		input = readline(""); // read input w/o promt - non-interactive mode
	if (input == NULL) //for ctrl_d, ...export 1 | export 1 | export 1
	{
		printf("exit\n");
		exit(0);
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
