# NAME = minishell

# CC = cc
# CFLAGS = -Wall -Wextra -Werror -Iincludes

# SRC = src/main.c \
#       src/ft_system.c \
#       src/ft_chdir.c \
# 	  src/signal_handler.c \
# 	  exec_filename/



LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
LIBFT_INCLUDE = -I$(LIBFTDIR)
LIBFT_LINK = -L$(LIBFTDIR) -lft

TOKENDIR = tokenizer
TOKEN = $(TOKENDIR)/libtokenizer.a
TOKEN_INCLUDE = -I$(TOKENDIR)
TOKEN_LINK = -L$(TOKENDIR) -ltokenizer



NAME	=	minishell

SRC_DIR			=	src
TOKENIZER_DIR	=	tokenizer
OBJ_DIR			=	obj

SRCS =	builtin_chdir.c \
		builtin_echo.c \
		builtin_env.c \
		builtin_exit.c \
		builtin_export.c \
		builtin_pwd.c \
		builtin_unset.c \
		env.c \
		ft_system.c \
		main.c \
		signal_handler.c \
		search_path.c

T_SRCS		=	ft_tokenizer.c \
				getpath.c

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFTDIR)/libft.a

OBJS		=	$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o)) $(addprefix $(OBJ_DIR)/,$(T_SRCS:.c=.o))
RLDIR = $(shell brew --prefix readline)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I./readline

all: $(NAME)

$(NAME): $(OBJS)
	@echo "set echo-control-characters off" > ~/.inputrc
	@make -C $(LIBFTDIR)
	@make -C $(TOKENDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LINK) $(TOKEN_LINK) -lreadline -L$(RLDIR)/lib

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include $(LIBFT_INCLUDE) $(TOKEN_INCLUDE)


$(OBJ_DIR)/%.o: $(TOKENIZER_DIR)/%.c
	@ $(CC) $(CFLAGS) -c -o $@ $<

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
