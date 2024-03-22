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
NAME = builtins

CC = clang
CCFLAGS = -Wall -Wextra -Werror
LIB = -lXext -lX11 -lm
LDLIBS := -lreadline -lhistory

RM = rm -f

DEPS = builtins.h \
	Libft/libft.h

SRCS_builtins = ft_echo.c \
	ztest.c \
	ft_cd.c \
	ft_pwd.c \
	ft_env.c \
	executormain.c \
	Heredoc/heredocmain.c \
	Heredoc/heredocchecks.c \
	Heredoc/heredocprocess.c \
	Pipes/pipefin.c \
	Redirections/redirmain.c \
	Redirections/newredirections.c \
	Redirections/longredirections.c \
	Redirections/doubleredirection.c \
	free.c \
	

SRCS_LIBFT = Libft/ft_atoi.c \
	Libft/ft_bzero.c \
	Libft/ft_calloc.c \
	Libft/ft_isalnum.c \
	Libft/ft_isalpha.c \
	Libft/ft_isascii.c \
	Libft/ft_isdigit.c \
	Libft/ft_isprint.c \
	Libft/ft_memchr.c \
	Libft/ft_memcmp.c \
	Libft/ft_memcpy.c \
	Libft/ft_memmove.c \
	Libft/ft_memset.c \
	Libft/ft_putchar_fd.c \
	Libft/ft_putendl_fd.c \
	Libft/ft_putnbr_fd.c  \
	Libft/ft_putstr_fd.c \
	Libft/ft_strchr.c \
	Libft/ft_striteri.c \
	Libft/ft_strlcat.c \
	Libft/ft_strlcpy.c \
	Libft/ft_strlen.c \
	Libft/ft_strmapi.c \
	Libft/ft_strncmp.c \
	Libft/ft_strnstr.c \
	Libft/ft_tolower.c \
	Libft/ft_toupper.c \
	Libft/ft_strdup.c \
	Libft/ft_strrchr.c \
	Libft/ft_substr.c \
	Libft/ft_strjoin.c \
	Libft/ft_itoa.c \
	Libft/ft_strtrim.c \
	Libft/ft_split.c

OBJS_LIBFT = $(SRCS_LIBFT:.c=.o)
OBJS_Builtins = $(SRCS_builtins:.c=.o)

ifeq ($(shell uname -s), Linux)
    CFLAGS += -D LINUX -Wno-unused-result
endif

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS_Builtins) $(OBJS_LIBFT)
	$(CC) -o $@ $^ $(LIB) $(LDLIBS)

clean:
	$(RM) $(OBJS_LIBFT)
	$(RM) $(OBJS_Builtins)

fclean: clean
	$(RM) ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus


