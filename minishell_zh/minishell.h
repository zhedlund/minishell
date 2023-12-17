#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAXARGS 10
#define WHITESPACE " \t\r\n\v"
#define SYMBOLS "<|>"

typedef struct s_cmd 
{
  int	type;          // ' ' (exec), | (pipe), '<' or '>' for redirection
}		t_cmd;

typedef struct s_exec
{
  int	type;              // ' '
  char	*argv[MAXARGS];   // arguments to the command to be exec-ed
}		t_exec;

typedef struct s_redir
{
  int	type;          // < or > 
  t_cmd	*cmd;   // the command to be run (e.g., an execcmd)
  char	*file;        // the input/output file
  int	mode;          // the mode to open the file with
  int	fd;            // the file descriptor number to use for the file
}		t_redir;

typedef struct s_pipe
{
  int	type;              // |
  t_cmd	*left;      // left side of pipe
  t_cmd	*right;     // right side of pipe
}		t_pipe;

/* lexing & parsing */
int		is_builtin(char *command);
char	**tokenizer(char *input, const char *delimiters);
int		parse_cmd_type(char **tokens);
char	*allocate_full_path(const char *token, const char *file);
char	*find_cmd_path(const char *file);
void	expand_variables(char **tokens);

/* execution */
int		exec_simple_cmd(const char *file, char *const argv[]);

/* utils */
char	*ft_strtok(char *str, const char *delim);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif