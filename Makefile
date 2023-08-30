# NAME = minishell

# CC = cc
# CFLAGS = -Wall -Wextra -Werror -Iincludes

# SRC = src/main.c \
#       src/ft_system.c \
#       src/ft_chdir.c \
# 	  src/signal_handler.c

# OBJS = $(SRC:.c=.o)
# OBJS := $(OBJS:src/%=obj/%)
# RLDIR = $(shell brew --prefix readline)

# LIBFTDIR = libft
# LIBFT = $(LIBFTDIR)/libft.a
# LIBFT_INCLUDE = -I$(LIBFTDIR)
# LIBFT_LINK = -L$(LIBFTDIR) -lft 


# all: $(NAME)

# $(NAME): $(OBJS)
# 	@echo "set echo-control-characters off" > ~/.inputrc
# 	@make -C $(LIBFTDIR)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LINK) -lreadline -L $(RLDIR)/lib

# obj/%.o: src/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include $(LIBFT_INCLUDE)

# $(OBJS): $(SRC)

# $(LIBFT):
# 	make -C $(LIBFTDIR)

# clean:
# 	rm -rf $(OBJS)
# 	make -C $(LIBFTDIR) clean

# fclean: clean
# 	rm -rf $(NAME)
# 	make -C $(LIBFTDIR) fclean

# re: fclean all


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
		signal_handler.c

T_SRCS		=	ft_tokenizer.c \
				getpath.c

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFTDIR)/libft.a

OBJS		=	$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o)) $(addprefix $(OBJ_DIR)/,$(T_SRCS:.c=.o))

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I./readline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@ $(CC) $(CFLAGS) -o minishell $(OBJS) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(OBJ_DIR)
	@ $(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(TOKENIZER_DIR)/%.c
	@ $(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@ rm -rf $(OBJ_DIR)
	@ make -C $(LIBFT_DIR) clean

fclean: clean
	@ rm -rf $(NAME)
	@ make -C $(LIBFT_DIR) fclean

re: fclean all
