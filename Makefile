NAME = minishell

all: $(NAME)

CC = gcc

CFLAGS = -lreadline -L /Users/ahernand/.brew/opt/readline/lib -I /Users/ahernand/.brew/opt/readline/include

SRCS =	srcs/files/minishell.c

OBJS = $(SRCS:%.c=%.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

test:
	make clean
	make
	@cd tester && bash test.sh
	make clean


# - - - - - - - - - - - - - - - - - #
# - - - - C L E A N I N G - - - - - #
# - - - - - - - - - - - - - - - - - #

clean:
	rm -f $(OBJS)
	rm -f minishell

fclean:
	make clean

re:	fclean all
