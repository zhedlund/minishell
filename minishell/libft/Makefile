# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 11:43:57 by zhedlund          #+#    #+#              #
#    Updated: 2024/02/25 19:07:20 by zhedlund         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_itoa.c ft_isdigit.c ft_isprint.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_splitme.c \
	ft_strcat.c ft_strcmp.c ft_strchr.c ft_strcpy.c ft_strdup.c \
	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strpbrk.c ft_strrchr.c \
	ft_strtok.c ft_tolower.c ft_toupper.c ft_strtrim.c ft_substr.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_isspace.c

BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c 

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	
all:	$(NAME)	

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

bonus:	$(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, bonus
