# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 16:15:35 by aderouba          #+#    #+#              #
#    Updated: 2022/11/17 13:45:06 by aderouba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS = --no-print-directory

NAME = pipex

SRC =	mandatory/pipex.c \
		mandatory/exec.c \
		mandatory/arg.c \
		mandatory/args.c

OBJ = ${SRC:.c=.o}

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
LIBFTFLAGS = -Llibft -lft
INCLUDES = -I. -Ilibft

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	@cd libft && make
	@echo "╔═══════════════╗"
	@echo "║Compiling pipex║"
	@echo "╚═══════════════╝"
	@$(CC) $^ $(LIBFTFLAGS) -o $@

all : $(NAME)

clean :
	@cd libft && make clean
	@rm -f $(OBJ)

fclean : clean
	@cd libft && make fclean
	@echo "╔══════════════╗"
	@echo "║Cleaning pipex║"
	@echo "╚══════════════╝"
	@rm -f $(NAME)

re : fclean $(NAME)
	@cd libft && make re

.PHONY: all clean fclean re
