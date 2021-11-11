NAME = minishell

LIBFT = srcs/libft/libft.a

all: $(NAME)

CC = gcc

CFLAGS = 

CFLAGS2 = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include

SRCS =	srcs/builtins/ft_echo.c			\
		srcs/builtins/ft_pwd.c			\
		srcs/builtins/ft_export.c		\
		srcs/builtins/ft_unset.c		\
		srcs/builtins/ft_env.c			\
		srcs/builtins/ft_cd.c			\
		srcs/files/ft_error.c			\
		srcs/files/ft_path.c			\
		srcs/files/ft_exe.c				\
		srcs/parse/parse.c				\
		srcs/parse/line.c				\
		srcs/parse/quotes.c				\
		srcs/parse/variables.c

SRCS2 = srcs/files/minishell.c

OBJS = $(SRCS:%.c=%.o)

OBJS2 = $(SRCS2:%.c=%.o)

#objs2: $(SRCS2)
#	echo palablk
#	$(CC) $(SRCS2) -c

$(LIBFT):
	cd srcs/libft && make 

$(NAME): $(OBJS) $(OBJS2) $(LIBFT)
	$(CC) $(CFLAGS2) $(OBJS) $(LIBFT) ./srcs/files/minishell.o -o $@


# - - - - - - - - - - - - - - - - - #
# - - - - C L E A N I N G - - - - - #
# - - - - - - - - - - - - - - - - - #

clean:
	rm -f $(OBJS) srcs/files/minishell.o
	rm -f minishell

fclean:
	make clean
	cd srcs/libft && make fclean
	rm -f srcs/libft/libft.a


re:	clean all
