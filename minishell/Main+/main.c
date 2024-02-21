/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:46 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/21 14:21:43 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

int g_signal = 0;

int	ft_whichsignalsub(char *signalarray, int ctrlc, char *buf, t_info **info)
{
	if (signalarray[0] != '|')
		(*info)->allcat = false;
	if (ft_strncmp(signalarray, "grep", ft_strlen(buf)) == 0)
		return (2);
	if (ft_strncmp(signalarray, "yes", ft_strlen(buf)) == 0)
		return (2);
	return (ctrlc);
}

int	ft_whichsignalfunction(char *buf, t_info **info)
{
	char	**signalarray;
	int	i;
	int	ctrlc;
	
	i = 0;
	ctrlc = 0;
	signalarray = ft_split(buf, ' ');
	(*info)->allcat = true;
	while (signalarray[i] != NULL)
	{
		if (ft_strncmp(signalarray[i], "cat", ft_strlen(buf)) == 0)
			ctrlc = 2; //include the options here and return true or false
		else if (ft_strncmp(signalarray[i], "wc", ft_strlen(buf)) == 0)
		{
			ctrlc = 2;
			if (signalarray[i + 1] != NULL && signalarray[i + 1][0] != '|')
				i++;
		}
		else
			ctrlc = ft_whichsignalsub(signalarray[i], ctrlc, buf, info);
		i++;
	}
	ft_freearray(signalarray);
	return (ctrlc);
}

void	ft_freelist(t_env **head)
{
	t_env	*node;
	t_env	*nodenext;

	node = (*head);
	while (node != NULL)
	{
		nodenext = (node->next);
		//printf("%d\n", node->field);
		free(node->field);
		free (node);
		node = NULL;
		node = nodenext;
	}
	node = NULL;
	nodenext = NULL;
	(*head) = NULL;
}

void	get_env(t_env **head)
{
	extern char	**environ;
	int	i;
	t_env	*temp;
	t_env	*node;

	i = 1;
	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		perror("malloc");
	node->field = ft_strdup(environ[0]);
	*head = node;
	while (environ[i] != NULL)
	{
		
		temp = (t_env *)malloc(sizeof(t_env));
		if (!temp)
			exit (1);
		temp->field = ft_strdup(environ[i]);
		node->next = temp;
		temp->prev = node;
		node = temp;
		node->next = NULL;
		i++;
	}
	temp = *head;
	temp->prev = node->next;
}

int has_unmatched_quotes(char *argv[])
{
	char	*str;
    int		single_quotes;
	int		double_quotes;
	int		i;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
    while (argv[i] != NULL)
    {
        str = argv[i];
        while (*str)
        {
			if (*str == '\"')
				double_quotes++;
			if (*str == '\'')
                single_quotes++;
            str++;
        }
		i++;
    }
	if ((single_quotes % 2 != 0) || (double_quotes % 2 != 0))
    	return (1);
	return (0);
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

void	ft_isitcat(char	*buf, t_info **info)
{
	char **cmdarray;
	int	count;
	int	catcount;
	int	catplus;

	count = 0;
	catcount = 0;
	catplus = 0;
	cmdarray = ft_split(buf, '|');
	while (cmdarray[count] != NULL)
	{
		cmdarray[count] = ft_strtrim(cmdarray[count], " ");
		if (ft_strlen("cat") == ft_strlen(cmdarray[count]) 
			&& ft_strncmp("cat", cmdarray[count], ft_strlen("cat")) == 0)
			catcount++;
		if (ft_strlen(cmdarray[count]) > ft_strlen("cat") &&
			ft_strncmp("cat ", cmdarray[count], ft_strlen("cat ")) == 0)
			catplus++;
		count++;
	}
	if (catplus != 0)
		(*info)->solocat = false;
	if (catcount == 0)
		(*info)->solocat = false;
	if (catcount !=0 && catplus == 0)
		(*info)->solocat = true;
	if (ft_strlen(cmdarray[0]) != ft_strlen("cat") 
		|| ft_strncmp("cat", cmdarray[0], ft_strlen("cat")) != 0)
		(*info)->solocat = false;
	ft_freearray(cmdarray);
}

int	is_whitespace(const char *buf)
{
    while (*buf != '\0')
	{
        if (!isspace(*buf))
            return (0);
        buf++;
    }
    return (1);
}

int main(void)
{
	static char	buf[1024];
	int			status; // variable to store exit status of child process
	t_info		*info;
	t_env		*head;

	status = 0;
	head = NULL;
	info = ft_calloc(sizeof(t_info), 1);
	get_env(&head);
	while (get_cmd(buf, sizeof(buf), &head, &info) >= 0)
	{
		ft_heredocmain(buf, &info);
		ft_isitcat(buf, &info);
		signal(SIGQUIT, ft_ctrlc); // put all signal related into a function (norm)
		signal(SIGINT, ft_ctrlc);
		if (ft_whichsignalfunction(buf, &info) == 2)
		{
			signal(SIGINT, ft_ctrlc2);
			signal(SIGQUIT, ft_ctrlc2);
		}
		if (is_whitespace(buf)) // make void function for input check (norm)
			continue ;
		if (has_unmatched_quotes((char *[]){buf, NULL}))
		{
			ft_putstr_fd("unmatched quote\n", 2);
			continue;
		}
		if (ft_disinherit(buf, &head, &info) == false && info->panic == false)
		{
				if (fork_process() == 0)
					run_cmd(parse_cmd(buf, &info, &head), &head, &info);
				wait(&status);
				if (WIFEXITED(status))
					info->exitstatus = WEXITSTATUS(status);
				status = info->exitstatus;
		}
		unlink("/tmp/hdtemp");
		info->hdcount = 0;
		info->catcount = 0;
		//anything else like this that needs resetting?
	}
	rl_clear_history();
	free(info);
	ft_freelist(&head);
	return(0);
}
