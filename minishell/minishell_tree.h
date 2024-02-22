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
#include <sys/ioctl.h>

#define MAXARGS 100
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
	char			*field;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_info
{	
	int		catcount;
	int		hdcount;
	bool	panic;
	char	**inputs;
	char	*input;
	bool	first;
	bool	unsetpath;
	bool	stillexecute;
	int		exitstatus;
	bool	allcat;
	int		infopid;
	int		infostatus;
	bool	inchild;
	bool	solocat;
	bool	aout;
	bool	cmdnf;
	bool	nospace;
	//t_env	*env;
}		t_info;

/* execution */
void	handle_exec_cmd(t_exec *exec_cmd, t_env **head, t_info **info);
void	handle_redir_cmd(t_redir *redir_cmd, t_env **head, t_info **info);
void	handle_child_process(t_cmd *cmd, int fd_pipe[], t_env **head, t_info **info);
void	handle_parent_process(t_cmd *cmd, int fd_pipe[], t_env **head, t_info **info);
void	handle_pipe_cmd(t_pipe *pipe_cmd, t_env **head, t_info **info);
int		fork_process(void);
void	run_cmd(t_cmd *cmd, t_env **head, t_info **info);
int		ft_execvp(t_exec *exec_cmd, char *const argv[], t_env **head, t_info **info);

/* constructors */
t_cmd	*exec_cmd(void);
t_cmd	*redir_cmd(t_cmd *sub_cmd, char *file, int type, t_info **info);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);

/* parsing */
t_cmd	*parse_cmd(char *str, t_info **info, t_env **head);
t_cmd	*parse_redir(t_cmd *cmd, char **position_ptr, char *end_str, t_info **info);
t_cmd	*parse_exec(char **position_ptr, char *end_str, t_info **info, t_env **head);
t_cmd	*parse_line(char **position_ptr, char *end_str, t_info **info, t_env **head);
int		get_cmd(char *buf, int nbuf, t_env **head, t_info **info);
int		get_token(char **input_ptr, char *end_str, char **token_start, char **token_end);
int		check_next_token(char **position_ptr, char *end_str, char *token_char);
void	parse_tokens(t_exec *exec_cmd, t_cmd **cmd, char **position_ptr, char *end_str, t_info **info, t_env **head);
char	*make_copy(char *start_ptr, char *end_ptr);
char	**expand_env(char **argv, t_env **head);
char	*expand_env_in_str(const char *str, int exit_status, t_env **head);
void	expand_exit_status(int exit_status, char *expanded, size_t *index);
void	ft_isitcat(char	*buf, t_info **info);
bool		has_unmatched_quotes(const char *input);

/* signals */
int		ft_whichsignalfunction(char *buf, t_info **info);
int		ft_whichsignalsub(char *signalarray, int ctrlc, char *buf, t_info **info);
void	ft_ctrlc(int sig);
void	ft_ctrlc2(int signal);

/* utils */
void	error_max_size(void);
int		is_whitespace(const char *buf);


/*libft stuff, remove when linked libft*/
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
int		ft_isalnum(int c);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
int		ft_isspace(char c);


/* unsorted stuff, builtins and signals mostly */
void	get_env(t_env **head);
void	ft_builtinsmenu(char *argv, char **cmdinfo, t_env **head, t_info **info);
void	ft_cd(char **cmdarray, t_env **head, t_info **info);
void	ft_env(char *arraystring, t_env **head, t_info **info, t_exec *exec_cmd);
void	ft_heredocexecute(char **hdarray, t_info **info);
void	ft_heredocmain(char *cmdline, t_info **info);
char	**ft_heredocarray(int heredoc, char **inputs);
void	ft_ctrlc(int sig);
void	ft_ctrlc2(int signal);
void	ft_unset(char *arraystring, t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_freelist(t_env **head);
void	ft_export(char **cmdarray, t_env **head, t_info **info);
int		ft_inititalchar(char *arraystring, t_info **info);
void	ft_unsetsub(char *inputi, t_env **head);
char	*ft_strjoin(char const *s1, char const *s2);
void    ft_pwd(char *arraystring, t_env **head, t_info **info, t_exec *exec_cmd);
void	ft_exportsub(char *toexport, t_env **head);
void    ft_echo(char *arraystring, t_exec *exec_cmd, t_env **head, t_info **info);
void    ft_exit(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_multifree(char *arraystring, t_env **head, t_info **info, t_exec *exec_cmd);
int		ft_disinherit(char *buf, t_env **head, t_info **info);
char	*ft_pathcheck(char *potentialpath, t_info **info, t_exec *exec_cmd, t_env **head);
char	*ft_findvalue(char *name, t_env **head);

#endif
