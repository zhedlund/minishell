#include "minishell_tree.h"

// compile: cc minishell_recursive.c minishell_utils.c ft_execvp.c expand_env.c -lreadline
// run: ./a.out

/* Execution */

/* exec_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void handle_exec_cmd(t_exec *exec_cmd)
{
    if (exec_cmd->argv[0] == 0)
    exit(0);
    ft_execvp(exec_cmd->argv[0], exec_cmd->argv);
}

/* redir_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void handle_redir_cmd(t_redir *redir_cmd)
{
    int fd_redirect;

    if (redir_cmd->type == '>' || redir_cmd->type == 'x')
	{
        if ((fd_redirect = open(redir_cmd->file, redir_cmd->mode, 0666)) < 0) // 0666 - read and write permissions for user, group, and others. no execution permissions
		{
			perror(redir_cmd->file);
            exit(2);
        }
    }
	else if (redir_cmd->type == '<')
	{
        if ((fd_redirect = open(redir_cmd->file, redir_cmd->mode)) < 0)
		{
			perror(redir_cmd->file);
            exit(2);
        }
    }
    if (dup2(fd_redirect, redir_cmd->fd) < 0)
	{
        perror("dup2");
        exit(1);
    }
    run_cmd(redir_cmd->cmd);
}

/* cmd: pointer to the command struct
	fd_pipe: file descriptor array
	return: void
	note: the function is called by: handle_pipe_cmd()
 */
void handle_child_process(t_cmd *cmd, int fd_pipe[])
{
    close(fd_pipe[1]);
    dup2(fd_pipe[0], STDIN_FILENO);
    run_cmd(((t_pipe *)cmd)->right);
    close(fd_pipe[0]);
}

/* cmd: pointer to the command struct
	fd_pipe: file descriptor array
	pid: process id
	return: void
	note: the function is called by: handle_pipe_cmd()
 */
void handle_parent_process(t_cmd *cmd, int fd_pipe[], pid_t pid)
{
    close(fd_pipe[0]);
    dup2(fd_pipe[1], STDOUT_FILENO);
    run_cmd(((t_pipe *)cmd)->left);
    close(fd_pipe[1]);
    wait(&pid);
}

/* pipe_cmd: pointer to the command struct
	return: void
	note: the function is called by: run_cmd()
 */
void handle_pipe_cmd(t_pipe *pipe_cmd)
{
    int		fd_pipe[2];
    pid_t	pid;

    if (pipe(fd_pipe) < 0)
	{
        perror("pipe");
        exit(1);
    }
    pid = fork();
    if (pid < 0)
	{
        perror("fork");
        exit(1);
    }
    if (pid == 0)
        handle_child_process((t_cmd *)pipe_cmd, fd_pipe);
    else
        handle_parent_process((t_cmd *)pipe_cmd, fd_pipe, pid);
}

/* cmd: pointer to the command struct
	return: void
	note: the function is called by: main()
 */
// Execute cmd.  Never returns.
void run_cmd(t_cmd *cmd)
{
    if (cmd == 0)
        exit(0);
    if (cmd->type == ' ')
        handle_exec_cmd((t_exec *)cmd);
    else if (cmd->type == '>' || cmd->type == '<' || cmd->type == 'x')
        handle_redir_cmd((t_redir *)cmd);
    else if (cmd->type == '|')
        handle_pipe_cmd((t_pipe *)cmd);
    else
	{
        //ft_putstr_fd("unknown run_cmd\n", 2);
		perror("run_cmd");
        exit(1);
    }
    exit(0);
}

/* buf: pointer to the buffer to store the input
	buf_size: size of the buffer
	return: 0 if input is not empty, -1 otherwise
	note: the function is called by: main()
 */
int	get_cmd(char *buf, int buf_size)
{
	char	*input;

	if (isatty(0)) // checks if connected to stdin (fd 0)
		input = readline("minishell> "); // read input w promt - interactive mode
	else
		input = readline(""); // read input w/o promt - non-interactive mode
	if (input == NULL || ft_strlen(input) == 0) // Handle EOF or empty input
	{
		if (input != NULL)
			free(input); // free memory allocated by readline()
		return (-1);
	}
	ft_strlcpy(buf, input, buf_size); // copy input to buf
	buf[buf_size - 1] = '\0'; // null-terminated string
    add_history(buf); // Add input to history
    free(input); // Free memory allocated by readline()
	return (0);
}

/* 	return: pid of the child process
	note: the function is called by: run_cmd()
 */
// Fork but perror on failure
int	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}

/* Constructors */

/* return: pointer to the command struct
	note: the function is called by: parse_exec()
 */
t_cmd	*exec_cmd(void)
{
	t_exec *cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = ' ';
	return ((t_cmd *)cmd);
}

/* sub_cmd: pointer to the command struct
	file: pointer to the file name
	type: redirection type
	return: pointer to the command struct
	note: the function is called by: parse_redir()
	note: memory allocated by malloc() must be freed by the caller
 */
t_cmd	*redir_cmd(t_cmd *sub_cmd, char *file, int type)
{
	t_redir *cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = type;
	cmd->cmd = sub_cmd;
	cmd->file = file;
	if (type == '<')
	{
		cmd->mode = O_RDONLY;
		cmd->fd = 0;
	}
	else if (type == 'x')
	{
		cmd->mode = O_WRONLY | O_CREAT | O_APPEND;
		cmd->fd = 1;
	}
	else
	{
		cmd->mode = O_WRONLY | O_CREAT | O_TRUNC;
		cmd->fd = 1;
	}
	return ((t_cmd *)cmd);
}

/* left: pointer to the left command struct
	right: pointer to the right command struct
	return: pointer to the command struct
	note: the function is called by: parse_pipe()
 */
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe *cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = '|';
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

/* Parsing */ 

/* input_ptr: pointer to the pointer to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	token_start: pointer to the pointer to the first character of the token
	token_end: pointer to the pointer to the last character of the token
	return: token type
	note: the function is called by: parse_redir(), parse_pipe(), parse_exec()
 */
// function too long, needs to be split
int	get_token(char **input_ptr, char *end_str, char **token_start, char **token_end)
{
    char	*current_pos;
    int		token_type;
	t_exec	*cmd;

    current_pos = *input_ptr;
    while (current_pos < end_str && ft_strchr(WHITESPACE, *current_pos))
        current_pos++;
    if (token_start != NULL)
        *token_start = current_pos;
    if (*current_pos == '\'') // Check for single-quoted string
    {
		token_type = 'q'; // Single-quoted string
		current_pos++;
        *token_start = current_pos;
        while (current_pos < end_str && *current_pos != '\'')
           	current_pos++;
        *token_end = current_pos;
		if (*current_pos == '\'')
        current_pos++;
    }
	else if (*current_pos == '\"') // Check for double-quoted string
	{
		token_type = 'd'; // Double-quoted string
		current_pos++;
		*token_start = current_pos;
		while (current_pos < end_str && *current_pos != '\"')
            current_pos++;
		*token_end = current_pos;
		if (*current_pos == '\"')
			current_pos++;
	}
	else if (*current_pos == 0)
        token_type = 0; // Null terminator
	else if (*current_pos == '|' || *current_pos == '<' || *current_pos == '>')
	{
        token_type = *current_pos;
		if (*current_pos == '>' && *(current_pos + 1) == '>') // append
		{
			token_type = 'x'; // append token type
			current_pos++;
		}
		current_pos++;
    }
	else
	{
        token_type = 'a'; // Default token type
        while (current_pos < end_str && !ft_strchr(WHITESPACE, *current_pos) && !ft_strchr(SYMBOLS, *current_pos))
            current_pos++;
    }
    if (token_end != NULL)
		*token_end = current_pos;
    while (current_pos < end_str && ft_strchr(WHITESPACE, *current_pos))
        current_pos++;
    *input_ptr = current_pos;
    return (token_type);
}

/* position_ptr: pointer to the pointer to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	token_char: pointer to the string of token characters
	return: 1 if the next token is a token character, 0 otherwise
	note: the function is called by: parse_redir(), parse_pipe(), parse_exec(), parse_cmd()
 */
int	check_next_token(char **position_ptr, char *end_str, char *token_char)
{
	char *current_pos;

	current_pos = *position_ptr;
	while (current_pos < end_str && ft_strchr(WHITESPACE, *current_pos))
		current_pos++;
	*position_ptr = current_pos;
	return (*current_pos && ft_strchr(token_char, *current_pos));
}

/* 	start_ptr: pointer to the first character of the string to be copied
	end_ptr: pointer to the last character of the string to be copied
	return: pointer to the copy of the string
	note: the copy is allocated on the heap and must be freed by the caller */
char	*make_copy(char *start_ptr, char *end_ptr)
{
	size_t len;
	char *copy;

	len = end_ptr - start_ptr;
	copy = malloc(len + 1);
	if (copy != NULL)
		ft_strlcpy(copy, start_ptr, len + 1); //copy n characters from s to c and ensure null-termination
	return (copy);
}

/* cmd: pointer to the command struct
	position_ptr: pointer to the pointer to the first character of 			expand_env(&exec_cmd->argv[args]);the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: parse_exec(), parse_redir(), parse_pipe(), parse_cmd(),
	run_cmd(), main(), get_cmd()
 */
t_cmd	*parse_redir(t_cmd *cmd, char **position_ptr, char *end_str)
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
            exit(EXIT_FAILURE);
        }
        if (redir_type == '<')
			cmd = redir_cmd(cmd, make_copy(file_start, file_end), '<');
		else if (redir_type == '>')
            cmd = redir_cmd(cmd, make_copy(file_start, file_end), '>');
		else if (redir_type == 'x')
			cmd = redir_cmd(cmd, make_copy(file_start, file_end), 'x');
        //else - handle unexpected token here if needed / print an error message)
    }
    return (cmd);
}

/* Function to handle token parsing and env expansion
	exec_cmd: pointer to the command struct
	cmd: pointer to the pointer to the command struct
	position_ptr: pointer to the pointer to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	note: the function is called by: parse_exec()
*/

void	parse_tokens(t_exec *exec_cmd, t_cmd **cmd, char **position_ptr, char *end_str)
{
    int		args;
    char	*token_start;
    char	*token_end;
    int		token_type;

	args = 0;
	while (!check_next_token(position_ptr, end_str, "|"))
	{
		token_type = get_token(position_ptr, end_str, &token_start, &token_end);
		if (token_type == 0)
			break;
		if (token_type == 'q' )
			exec_cmd->argv[args] = make_copy(token_start, token_end - 1); // Exclude the ending quote
		else if (token_type == 'd')
		{
			exec_cmd->argv[args] = make_copy(token_start, token_end - 1); // Exclude the ending quote
			expand_env_in_quotes(exec_cmd->argv[args]); // Expand environment variables within double-quoted strings
		}
		else
		{
			exec_cmd->argv[args] = make_copy(token_start, token_end);
			expand_env_in_quotes(exec_cmd->argv[args]);
		}
		args++;
		if (args >= MAXARGS)
			ft_putstr_fd("Too many arguments\n", 2);
		*cmd = parse_redir(*cmd, position_ptr, end_str);
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

/* ps: pointer to the pointer to the first character of the string to be parsed
	es: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is recursive
	note: the function is called by: parse_line(), parse_cmd(), run_cmd(), main(), get_cmd()
 */
t_cmd	*parse_pipe(char **position_ptr, char *end_str)
{
	t_cmd *cmd;

	cmd = parse_exec(position_ptr, end_str);
	if (check_next_token(position_ptr, end_str, "|"))
	{
		get_token(position_ptr, end_str, 0, 0);
		cmd = pipe_cmd(cmd, parse_pipe(position_ptr, end_str));
	}
	return (cmd);
}

/* position_ptr: pointer to the pointer to the first character of the string to be parsed
	end_str: pointer to the last character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: parse_cmd()
 */
t_cmd	*parse_line(char **position_ptr, char *end_str)
{
	t_cmd *cmd;

	cmd = parse_pipe(position_ptr, end_str);
	return (cmd);
}

/* str: pointer to the first character of the string to be parsed
	return: pointer to the command struct
	note: the function is called by: main()
 */
t_cmd	*parse_cmd(char *str)
{
	char	*end_str;
	t_cmd	*cmd;

	end_str = str + ft_strlen(str);
	cmd = parse_line(&str, end_str);
	check_next_token(&str, end_str, "");
	if (str != end_str)
	{
		ft_putstr_fd("leftovers in str\n", 2);
		exit(EXIT_FAILURE);
	}
	return (cmd);
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


/* Main */

int main(void)
{
	static char	buf[100];
	int			status; // variable to store exit status of child process
	int			exit_status;
	
	while (get_cmd(buf, sizeof(buf)) >= 0)
	{	
        // Check for unmatched quotes before proceeding
		if (has_unmatched_quotes((char *[]){buf, NULL}))
		{
			ft_putstr_fd("unmatched quote\n", 2);
			continue; // Skip processing this command and move to the next one
		}
		// cd is just an example, will call builtin functions here
		// if (is_builtin()) or similar
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ') 
		{
			// Chdir have to be run in the parent, has no effect if run in the child.
			buf[ft_strlen(buf) - 1] = 0; // chop \n
			if (chdir(buf + 3) < 0)
				ft_putstr_fd("cannot cd\n", 2);
			continue;
		}
		if (fork_process() == 0)
			run_cmd(parse_cmd(buf));
		wait(&status);
		//waitpid(pid, &status, 0);
		if (WIFEXITED(status))
				exit_status = (WEXITSTATUS(status)); // WEXITSTATUS returns the exit status of the child
    	printf("Child exit status: %d\n", exit_status); // just prints status for now
	}
	return (0);
}
