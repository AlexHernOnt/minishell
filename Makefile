# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahernand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 13:35:22 by ahernand          #+#    #+#              #
#    Updated: 2022/01/29 17:54:52 by amorion-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = srcs/libft/libft.a

all: $(NAME)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CFLAGS2 = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include

SRCS =	srcs/builtins/ft_echo.c			\
		srcs/builtins/ft_pwd.c			\
		srcs/builtins/ft_export.c		\
		srcs/builtins/ft_no_quotes.c	\
		srcs/builtins/ft_unset.c		\
		srcs/builtins/ft_env.c			\
		srcs/builtins/ft_cd.c			\
		srcs/exe/ft_redir.c				\
		srcs/exe/ft_path.c				\
		srcs/exe/ft_exe.c				\
		srcs/exe/ft_cmd_no_builtin.c	\
		srcs/exe/ft_collect_info_line.c	\
		srcs/exe/ft_organizer.c			\
		srcs/exe/ft_directions.c		\
		srcs/exe/ft_pipes.c				\
		srcs/files/ft_error.c			\
		srcs/files/frees_functions.c	\
		srcs/files/control.c			\
		srcs/parse/parse.c				\
		srcs/parse/line.c				\
		srcs/parse/quotes.c				\
		srcs/parse/variables.c			\
		srcs/parse/utils.c				

SRCS2 = srcs/files/minishell.c

OBJS = $(SRCS:%.c=%.o)

OBJS2 = $(SRCS2:%.c=%.o)

$(LIBFT):
	cd srcs/libft && make 

$(NAME): $(OBJS) $(OBJS2) $(LIBFT)
	$(CC) $(CFLAGS2) $(OBJS) $(OBJS2) $(LIBFT) -o $@


# - - - - - - - - - - - - - - - - - #
# - - - - C L E A N I N G - - - - - #
# - - - - - - - - - - - - - - - - - #

clean:
	rm -f $(OBJS) srcs/files/minishell.o
	rm -f $(NAME)

fclean:
	make clean
	cd srcs/libft && make fclean
	rm -f srcs/libft/libft.a

re:	clean all

.PHONY: re clean fclean all
