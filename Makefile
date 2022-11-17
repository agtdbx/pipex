# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 16:15:35 by aderouba          #+#    #+#              #
#    Updated: 2022/11/17 17:05:24 by aderouba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS = --no-print-directory

NAME = pipex

SRC =	mandatory/pipex.c \
		mandatory/exec.c \
		mandatory/arg.c \
		mandatory/args.c

SRC_BONUS =	bonus/pipex_bonus.c \
			bonus/exec_bonus.c \
			bonus/arg_bonus.c \
			bonus/args_bonus.c

ifdef BONUS
	SRC = $(SRC_BONUS)
endif

OBJ = ${SRC:.c=.o}
OBJ_BONUS = ${SRC_BONUS:.c=.o}

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
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean : clean
	@cd libft && make fclean
	@echo "╔══════════════╗"
	@echo "║Cleaning pipex║"
	@echo "╚══════════════╝"
	@rm -f $(NAME)

re : fclean $(NAME)
	@cd libft && make re

bonus :
	@make BONUS=42

.PHONY: all clean fclean re bonus
