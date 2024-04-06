# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:02:43 by jelliott          #+#    #+#              #
#    Updated: 2024/03/26 18:13:25 by zhedlund         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
COMPILED = .compiled

SRC = main.c \
    builtins/ft_disinherit.c \
    builtins/ft_cd.c \
    builtins/cd_home.c \
    builtins/prebuiltins.c \
    builtins/cd_path_find.c \
    builtins/ft_echo.c \
    builtins/ft_env.c \
    builtins/ft_exit.c \
    builtins/ft_export.c \
    builtins/ft_export_syntax.c \
    builtins/export_utils.c \
    builtins/ft_pathcheck.c \
    builtins/ft_pwd.c \
    builtins/ft_unset.c \
    execution/constructors.c \
    execution/ft_execvp.c \
    execution/handle_paths.c \
    execution/pipes.c \
    execution/redirections.c \
    execution/run_cmd.c \
    heredoc/hdmain.c \
    heredoc/hdprocess.c \
    heredoc/hdprocess_prep.c \
    parsing/expand_env.c \
    parsing/expand_exit_status.c \
    parsing/ft_isitcat.c \
    parsing/find_relative_env.c \
    parsing/get_cmd.c \
    parsing/get_token.c \
    parsing/has_unmatched_quotes.c \
    parsing/parse_cmd.c \
    parsing/parse_tokens.c \
    signals/signal_handler.c \
	signals/whichsignal.c \
    utils/free.c \
    utils/minishell_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -s -C $(LIBFTDIR)

$(NAME): $(OBJ) $(LIBFT)
	@printf "Compiling: [\033[0;32m"
	@$(MAKE) progress -s
	@printf "\033[0m] Done\n"
	@$(CC) $(OBJ) $(LFLAGS) -o $(NAME) -L$(LIBFTDIR) -lft
	@touch $(COMPILED)

progress:
	@for i in $(shell seq 1 10); do \
		sleep 0.1; \
		printf "="; \
	done

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ) $(COMPILED)
	@make -s -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME) $(COMPILED)
	@make -s -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re progress
