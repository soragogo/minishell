#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../libft/libft.h"
#include "../tokenizer/token.h"
int ft_system(t_token *tokens, int *status);
int ft_chdir(char *command_buf);
void ft_signals(void);
void waitline();
t_token *search_path(t_token *tokens);
#endif
