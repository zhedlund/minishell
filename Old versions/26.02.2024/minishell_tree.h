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

#define MAXARGS 50
#define WHITESPACE " \t\r\n\v"
#define SYMBOLS "<|>"

extern int g_signal;

typedef struct s_cmd 
{
  int	type;          // ' ' (exec), | (pipe), '<','>', 'x' (append/">>")
}		t_cmd;

typedef struct s_exec
{
  int	type;              // ' '
  char	*argv[MAXARGS];   // arguments to the command to be executed
}		t_exec;

typedef struct s_redir
{
  int	type;          // <, >, x (append/>>)
  t_cmd	*cmd;   // the command to be run (e.g., an execcmd)
  char	*file;        // the input/output file
  int	mode;          // the mode to open the file with
  int	fd;            // the file descriptor number to use for the file
  bool	first;
}		t_redir;

typedef struct s_pipe
{
  int	type;              // |
  t_cmd	*left;      // left side of pipe
  t_cmd	*right;     // right side of pipe
}		t_pipe;

typedef struct s_env
{
	char		*field;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_info
{	
	int	catcount;
	int	hdcount;
	bool	panic;
	char	*collect;
	char	*tmpfile;
	char	**inputs;
	char	*input;
	bool	first;
	//t_env	*env;
}		t_info;

/* execution */
void	handle_exec_cmd(t_exec *exec_cmd, t_env **head);
void	handle_redir_cmd(t_redir *redir_cmd, t_env **head);
void	handle_child_process(t_cmd *cmd, int fd_pipe[], int pid, t_env **head);
void	handle_parent_process(t_cmd *cmd, int fd_pipe[], int pid, int status, t_env **head);
void	handle_pipe_cmd(t_pipe *pipe_cmd, t_env **head);
int		get_cmd(char *buf, int nbuf, t_env **head);
int		fork_process(void);
void 	run_cmd(t_cmd *cmd, t_env **head);
int		ft_execvp(const char *file, char *const argv[], t_env **head);

/* constructors */
t_cmd	*exec_cmd(void);
t_cmd	*redir_cmd(t_cmd *sub_cmd, char *file, int type, t_info **info);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);

/* parsing */
t_cmd	*parse_cmd(char *str, t_info **info);
t_cmd	*parse_redir(t_cmd *cmd, char **position_ptr, char *end_str, t_info **info);
t_cmd	*parse_exec(char **position_ptr, char *end_str, t_info **info);
t_cmd	*parse_line(char **position_ptr, char *end_str, t_info **info);
int		get_token(char **input_ptr, char *end_str, char **token_start, char **token_end);
int		check_next_token(char **position_ptr, char *end_str, char *token_char);
char	*make_copy(char *start_ptr, char *end_ptr);
char	**expand_env(char **argv);

/* utils */
char	*ft_strtok(char *str, const char *delim);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_freearray(char **tofree);

int main(void);
char **expand_env(char **argv);
int	ft_builtinsmenu(char *argv, t_env **head);
int   ft_cd(char *arraystring);
int   ft_env(char *arraystring, t_env **head);
void	ft_heredocexecute(char **hdarray, t_info **info);
void	ft_heredocmain(char *cmdline, t_info **info);
char	**ft_heredocarray(int heredoc, char **inputs);
void	ft_ctrlc(int sig);
void	ft_ctrlc2(int signal);
int    ft_unset(char *arraystring, t_env **head);
void  ft_freelist(t_env **head);

#endif
