NAME = minishell

CC = cc

#CFLAGS = -Wall -Wextra -Werror -Iincludes
CFLAGS = -Iincludes

SRC = src/main.c \
      src/ft_system.c \
      src/ft_chdir.c

OBJS = $(SRC:.c=.o)
OBJS := $(OBJS:src/%=obj/%)


all:$(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS):$(SRC)

clean:
	rm -rf $(OBJS)

fclean:clean
	rm -rf $(NAME)

re:fclean
	make all
