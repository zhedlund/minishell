// Simplifed xv6 shell.

#include "minishell.h"

int fork1(void); // Fork but exits on failure.
t_cmd *parse_cmd(char *);

// Execute cmd.  Never returns.
void run_cmd(t_cmd *cmd)
{
	int fd_redirect;
	int p_id;
	int fd_pipe[2];
	t_exec *exec_cmd;
	t_pipe *pipe_cmd;
	t_redir *redir_cmd;

	if (cmd == 0)
		exit(0);

	switch (cmd->type)
	{
	default:
		fprintf(stderr, "unknown run_cmd\n");
		exit(-1);
	case ' ':
		exec_cmd = (t_exec *)cmd;
		if (exec_cmd->argv[0] == 0)
			exit(0);
		// fprintf(stderr, "exec not implemented\n");
		execvp(exec_cmd->argv[0], exec_cmd->argv);
		break;
	case '>':
	case '<':
		redir_cmd = (t_redir *)cmd;
		// fprintf(stderr, "redir not implemented\n");
		if (redir_cmd->type == '>')
		{
			if ((fd_redirect = open(redir_cmd->file, redir_cmd->mode, 0666)) < 0)
			{
				fprintf(stderr, "open %s has failed\n", redir_cmd->file);
				exit(0);
			}
		}
		else if (redir_cmd->type == '<')
		{
			if ((fd_redirect = open(redir_cmd->file, redir_cmd->mode)) < 0)
			{
				fprintf(stderr, "open %s has failed\n", redir_cmd->file);
				exit(0);
			}
		}
		if (dup2(fd_redirect, redir_cmd->fd) < 0)
		{
			fprintf(stderr, "dup2 has failed\n");
			exit(0);
		}
		run_cmd(redir_cmd->cmd);
		break;
	case '|':
		pipe_cmd = (t_pipe *)cmd;
		// fprintf(stderr, "pipe not implemented\n");
		if (pipe(fd_pipe) < 0)
		{
			fprintf(stderr, "pipe has failed\n");
			exit(0);
		}
		if ((p_id = fork()) < 0)
		{
			fprintf(stderr, "fork has failed\n");
			exit(0);
		}
		else if (p_id == 0)
		{
			close(fd_pipe[1]);
			dup2(fd_pipe[0], STDIN_FILENO);
			run_cmd(pipe_cmd->right);
			close(fd_pipe[0]);
		}
		else
		{
			close(fd_pipe[0]);
			dup2(fd_pipe[1], STDOUT_FILENO);
			run_cmd(pipe_cmd->left);
			close(fd_pipe[1]);
			wait(&p_id);
		}
		break;
	}
	exit(0);
}

int get_cmd(char *buf, int nbuf)
{
	if (isatty(fileno(stdin)))
		fprintf(stdout, "cs3224> ");
	memset(buf, 0, nbuf);
	fgets(buf, nbuf, stdin);
	if (buf[0] == 0) // EOF
		return -1;
	return 0;
}

int main(void)
{
	static char buf[100];
	int fd, r;
	// Read and run input commands.
	while (get_cmd(buf, sizeof(buf)) >= 0)
	{
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			// Clumsy but will have to do for now.
			// Chdir has no effect on the parent if run in the child.
			buf[strlen(buf) - 1] = 0; // chop \n
			if (chdir(buf + 3) < 0)
				fprintf(stderr, "cannot cd %s\n", buf + 3);
			continue;
		}
		if (fork1() == 0)
			run_cmd(parse_cmd(buf));
		wait(&r);
	}
	exit(0);
}

int fork1(void)
{
	int pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return pid;
}

t_cmd *exec_cmd(void)
{
	t_exec *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = ' ';
	return (t_cmd *)cmd;
}

t_cmd *redir_cmd(t_cmd *sub_cmd, char *file, int type)
{
	t_redir *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = type;
	cmd->cmd = sub_cmd;
	cmd->file = file;
	cmd->mode = (type == '<') ? O_RDONLY : O_WRONLY | O_CREAT | O_TRUNC;
	cmd->fd = (type == '<') ? 0 : 1;
	return (t_cmd *)cmd;
}

t_cmd *pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = '|';
	cmd->left = left;
	cmd->right = right;
	return (t_cmd *)cmd;
}

// Parsing

//char whitespace[] = " \t\r\n\v";
//char symbols[] = "<|>";

int get_token(char **input_ptr, char *end_str, char **token_start, char **token_end)
{
  char *current_pos;
  int token_type;
  
  current_pos = *input_ptr;
  while (current_pos < end_str && strchr(WHITESPACE, *current_pos))
    current_pos++;

  if (token_start)
    *token_start = current_pos;

  token_type = *current_pos;

  switch (*current_pos) {
    case 0:
      break;
    case '|':
    case '<':
      current_pos++;
      break;
    case '>':
      current_pos++;
      break;
    default:
      token_type = 'a';
      while (current_pos < end_str && !strchr(WHITESPACE, *current_pos) && !strchr(SYMBOLS, *current_pos))
        current_pos++;
      break;
  }

  if (token_end)
    *token_end = current_pos;

  while (current_pos < end_str && strchr(WHITESPACE, *current_pos))
    current_pos++;

  *input_ptr = current_pos;

  return token_type;
}


int peek(char **ps, char *es, char *toks)
{
	char *s;

	s = *ps;
	while (s < es && strchr(WHITESPACE, *s))
		s++;
	*ps = s;
	return *s && strchr(toks, *s);
}

t_cmd *parse_line(char **, char *);
t_cmd *parse_pipe(char **, char *);
t_cmd *parse_exec(char **, char *);

// make a copy of the characters in the input buffer, starting from s through es.
// null-terminate the copy to make it a string.
char *make_copy(char *s, char *es)
{
	int n = es - s;
	char *c = malloc(n + 1);
	//assert(c);
	strncpy(c, s, n);
	c[n] = 0;
	return c;
}

t_cmd	*parse_cmd(char *s)
{
	char *es;
	t_cmd *cmd;

	es = s + strlen(s);
	cmd = parse_line(&s, es);
	peek(&s, es, "");
	if (s != es)
	{
		fprintf(stderr, "leftovers: %s\n", s);
		exit(-1);
	}
	return cmd;
}

t_cmd	*parse_line(char **ps, char *es)
{
	t_cmd *cmd;
	cmd = parse_pipe(ps, es);
	return cmd;
}

t_cmd	*parse_pipe(char **ps, char *es)
{
	t_cmd *cmd;

	cmd = parse_exec(ps, es);
	if (peek(ps, es, "|"))
	{
		get_token(ps, es, 0, 0);
		cmd = pipe_cmd(cmd, parse_pipe(ps, es));
	}
	return cmd;
}

t_cmd*	parse_redir(t_cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q, *eq;

	while (peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);
		if (get_token(ps, es, &q, &eq) != 'a')
		{
			fprintf(stderr, "missing file for redirection\n");
			exit(-1);
		}
		switch (tok)
		{
		case '<':
			cmd = redir_cmd(cmd, make_copy(q, eq), '<');
			break;
		case '>':
			cmd = redir_cmd(cmd, make_copy(q, eq), '>');
			break;
		}
	}
	return cmd;
}

t_cmd *parse_exec(char **ps, char *es)
{
	char *q, *eq;
	int tok, argc;
	t_exec *cmd;
	t_cmd *ret;

	ret = exec_cmd();
	cmd = (t_exec *)ret;

	argc = 0;
	ret = parse_redir(ret, ps, es);
	while (!peek(ps, es, "|"))
	{
		if ((tok = get_token(ps, es, &q, &eq)) == 0)
			break;
		if (tok != 'a')
		{
			fprintf(stderr, "syntax error\n");
			exit(-1);
		}
		cmd->argv[argc] = make_copy(q, eq);
		argc++;
		if (argc >= MAXARGS)
		{
			fprintf(stderr, "too many args\n");
			exit(-1);
		}
		ret = parse_redir(ret, ps, es);
	}
	cmd->argv[argc] = 0;
	return ret;
}