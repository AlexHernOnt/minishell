NAME = minishell

all: $(NAME)

CC = gcc

CFLAGS = 

CFLAGS2 = -lreadline

SRCS =	srcs/builtins/ft_echo.c \
		srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_export.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_cd.c \
		srcs/libft/ft_strdup.c \
		srcs/libft/ft_strlen.c

SRCS2 = srcs/files/minishell.c

OBJS = $(SRCS:%.c=%.o)

OBJS2 = $(SRCS2:%.c=%.o)

#objs2: $(SRCS2)
#	echo palablk
#	$(CC) $(SRCS2) -c



$(NAME): $(OBJS) $(OBJS2)
	$(CC) $(CFLAGS2) $(OBJS) ./srcs/files/minishell.o -o $@

test:
	make clean
	make
	@cd tester && bash test.sh
	make clean


# - - - - - - - - - - - - - - - - - #
# - - - - C L E A N I N G - - - - - #
# - - - - - - - - - - - - - - - - - #

clean:
	rm -f $(OBJS) minishell.o
	rm -f minishell

fclean:
	make clean

re:	fclean all
