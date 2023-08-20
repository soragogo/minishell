NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes

SRC = src/main.c \
      src/ft_system.c \
      src/ft_chdir.c \
	  src/signal_handler.c

OBJS = $(SRC:.c=.o)
OBJS := $(OBJS:src/%=obj/%)
RLDIR = $(shell brew --prefix readline)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "set echo-control-characters off" > ~/.inputrc
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline -L $(RLDIR)/lib

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include

$(OBJS): $(SRC)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

