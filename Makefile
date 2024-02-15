# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:02:43 by jelliott          #+#    #+#              #
#    Updated: 2024/02/15 14:17:54 by zhedlund         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline

SRC = Main+/main.c \
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

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) (LFLAGS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re