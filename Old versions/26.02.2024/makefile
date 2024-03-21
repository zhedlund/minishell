# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    make                                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:02:43 by jelliott          #+#    #+#              #
#    Updated: 2023/12/11 16:02:53 by jelliott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = Minishell

CC = clang
CCFLAGS = -Wall -Wextra -Werror -g
LIB = -lXext -lX11 -lm
LDLIBS := -lreadline -lhistory

RM = rm -f

DEPS = minishell_tree.h

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

OBJS_Minishell = $(SRCS_Minishell:.c=.o)

ifeq ($(shell uname -s), Linux)
    CFLAGS += -D LINUX -Wno-unused-result
endif

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS_Minishell)
	$(CC) -o $@ $^ $(LIB) $(LDLIBS)

clean:
	$(RM) $(OBJS_Minishell)

fclean: clean
	$(RM) ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus


