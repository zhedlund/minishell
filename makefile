# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:02:43 by jelliott          #+#    #+#              #
#    Updated: 2024/02/14 19:58:08 by zhedlund         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CCFLAGS = -Wall -Wextra -Werror -g
LDLIBS := -lreadline

RM = rm -f

SRCS_Minishell = Main+/main.c \
	Main+/cmdsinitial.c \
	Parsing/constructors.c \
	Parsing/parsing1.c \
	Parsing/parsing2.c \
	Parsing/parsing3.c \
	Pipes/pipes.c \
	Redirections/redirections.c \
	Simple_Commands/exec_simple.c \
	Utils/minishell_utils.c \
	Utils/ft_split.c \
	Utils/ft_strtrim.c \
	Utils/free.c \
	expand_env.c \
	Simple_Commands/ft_execvp.c \
	Simple_Commands/ft_builtinsmenu.c \
	Simple_Commands/ft_cd.c \
	Simple_Commands/ft_env.c \
	Heredoc/hdmain.c \
	Heredoc/hdprocess.c \
	Simple_Commands/ft_unset.c \
	Simple_Commands/ft_export.c \
	Simple_Commands/ft_pwd.c \
	Simple_Commands/ft_echo.c \
	Simple_Commands/ft_exit.c \

OBJS_Minishell = $(SRCS_Minishell:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS_Minishell)
	$(CC) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(OBJS_Minishell)

fclean: clean
	$(RM) ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus