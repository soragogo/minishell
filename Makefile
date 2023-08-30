NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRC = src/main.c \
      src/ft_system.c \
      src/ft_chdir.c \
	  src/signal_handler.c \
	  exec_filename/search_path.c

OBJS = $(SRC:.c=.o)
OBJS := $(OBJS:src/%=obj/%)
RLDIR = $(shell brew --prefix readline)

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
LIBFT_INCLUDE = -I$(LIBFTDIR)
LIBFT_LINK = -L$(LIBFTDIR) -lft

TOKENDIR = tokenizer
TOKEN = $(TOKENDIR)/libtokenizer.a
TOKEN_INCLUDE = -I$(TOKENDIR)
TOKEN_LINK = -L$(TOKENDIR) -ltokenizer


all: $(NAME)

$(NAME): $(OBJS)
	@echo "set echo-control-characters off" > ~/.inputrc
	@make -C $(LIBFTDIR)
	@make -C $(TOKENDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LINK) $(TOKEN_LINK) -lreadline -L $(RLDIR)/lib

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include $(LIBFT_INCLUDE) $(TOKEN_INCLUDE)

$(OBJS): $(SRC)

$(LIBFT):
	make -C $(LIBFTDIR)
$(TOKEN):
	make -C $(TOKENDIR)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFTDIR) clean
	make -C $(TOKENDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFTDIR) fclean
	make -C $(TOKENDIR) fclean

re: fclean all

