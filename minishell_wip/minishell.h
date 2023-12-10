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
#include <readline/readline.h>
#include <readline/history.h>

/* lexing & parsing */
int		is_builtin(char *command);
char	**tokenizer(char *input, const char *delimiters);
int		parse_cmd_type(char **tokens);
char	*allocate_full_path(const char *token, const char *file);
char	*find_command_path(const char *file);

/* execution */
int		execute_simple_command(const char *file, char *const argv[]);

/* utils */
char	*ft_strtok(char *str, const char *delim);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif