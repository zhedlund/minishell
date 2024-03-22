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
	bool	pipe;
	bool	firstcommandmix;
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
	int	runhere;
	bool  exiting;
	char	*expanded; //not being used, but is sent to multifree, so I'm leaving it in for now
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
int	get_cmd(char *buf, int nbuf, t_env **head, t_info **info);
int	get_token(char **input_ptr, char *end_str, char **token_start, char **token_end);
int	check_next_token(char **position_ptr, char *end_str, char *token_char);
void	parse_tokens(t_exec *exec_cmd, t_cmd **cmd, char **position_ptr, char *end_str, t_info **info, t_env **head);
char	*make_copy(char *start_ptr, char *end_ptr);
char	**expand_env(char **argv, t_env **head);
char	*expand_env_in_str(const char *str, int exit_status);
void	expand_exit_status(int exit_status, char *expanded, size_t *index);
void	ft_isitcat(char	*buf, t_info **info);
bool		has_unmatched_quotes(const char *input);

/* signals */
int		ft_whichsignalfunction(char *buf, t_info **info);
void	ft_ctrlc(int sig);
void	ft_ctrlc2(int signal);
bool	ft_greponearguement(char *totest);
void	ft_othercommands(char **firstcommandarray, t_info **info);
int		ft_firstcommandcheck(char *buf, t_info **info);
int		ft_nopipe(char **signalarray, int i, t_info **info, char *buf);
int		ft_igreatertwo(char **signalarray, t_info **info, int ctrlc);
char	**ft_arraytrim(char **totrim);
/* utils */
void	error_max_size(void);
int		is_whitespace(const char *buf);
bool	ft_identical(char *a, char *b);

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
void	ft_putendl_fd(char *s, int fd);

//heredoc
void	ft_hdctrld(char *input, t_info **info, char *hdarray);
void	ft_hdprocess(char **hdarray, t_info **info, int fd, char *input);
char	**ft_heredocarray(int heredoc, char **inputs);
//static void	ft_hdsigint(int signal);
void	ft_hdprocess_prep(t_info **info, char **hdarray);
void	ft_heredocexecute(char **hdarray, t_info **info);
bool	ft_validheredoc(t_info **info, bool direct, int heredoc, char *file);
void	ft_hdcountsub(char **temp, int i, t_info **info);
void	ft_hdcount(char **temp, t_info **info, char **inputs);
char	**ft_checkheredoc(char **inputs, t_info **info);
void	ft_heredocmain(char *cmdline, t_info **info);

//builtin/execution related
void	ft_exiting(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_itisapath(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_is_it_a_command(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_command_not_found(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_builtins_not_env(t_exec *exec_cmd, t_env **head, t_info **info);
bool	ft_isitapath(char *input);
void	ft_pathexperiment(t_exec *exec_cmd, t_info **info, t_env **head);
void	ft_is_there_a_path(char *temp, t_exec *exec_cmd);
char	*ft_is_there_a_path_sub(char **path_options, char *hold);
char	*ft_pathcheck(char *potentialpath, t_info **info, t_exec *exec_cmd, t_env **head);
bool	ft_checkdirectory(char	*tocheck);
int	ft_choice(const char *file);
char	*ft_shorten(const char	*file);

//builtins
//cd functions
char	*ft_home(char *locate, t_env **head, t_info **info);
char	*ft_gethome(t_env **head, char *locate);
bool	ft_homeset(t_env **head);
char	*ft_cdsub(char *arraystring);
char	*ft_path(char *former);
char	*ft_backone_sub(char *locate, int i);
char	*ft_backone(char *locate);
void	ft_move(char *locate, t_env **head, t_info **info);
void	ft_cd_finish(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_cd_execute(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_cd(t_exec *exec_cmd, t_env **head, t_info **info);

//echo functions
void	ft_printout(int a, char **cmdargs, bool newline);
void	ft_echo(t_exec *exec_cmd, t_env **head, t_info **info);

//pwd functions
void	ft_pwd(t_env **head, t_info **info, t_exec *exec_cmd);
//void	ft_multifree(char *a, t_env **head, t_info **info, t_exec *exec_cmd);

//env functions
void	ft_env(char *arraystring, t_env **head, t_info **info, t_exec *exec_cmd);

//exit functions
void	ft_exit(t_exec *exec_cmd, t_env **head, t_info **info);

//unset functions
void	ft_unset(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_unset_end_free(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_unsetsub(char *inputi, t_env **head);
void	ft_list_middle(t_env *temp);
void	ft_list_start_end(t_env **head, t_env *temp, bool start);

//export functions
void	ft_exportfree(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_invalid_identifier(t_env **head, t_info **info, t_exec *exec_cmd);
int ft_valididentifier(char *check);
bool	ft_unexpectedtoken(char *check);
bool	ft_syntax_check(t_exec *exec_cmd, t_env **head, t_info **info);
bool	ft_equalpresent(char *check);
void	ft_exportsub(char *toexport, t_env **head);
void	ft_solo_export(t_env **head, t_info **info, t_exec *exec_cmd);
void	valid_identifier_export(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_export(t_exec *exec_cmd, t_env **head, t_info **info);

/* unsorted stuff, builtins and signals mostly */
void	get_env(t_env **head);
void	ft_ctrlc(int sig);
void	ft_ctrlc2(int signal);
void	ft_freelist(t_env **head);
int		ft_inititalchar(char *arraystring, t_info **info);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_multifree(char *arraystring, t_env **head, t_info **info, t_exec *exec_cmd);
int		ft_disinherit(char *buf, t_env **head, t_info **info);
char	*ft_findvalue(char *name, t_env **head);

#endif
