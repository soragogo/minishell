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
#include <limits.h>

#include "../libft/libft.h"
#include "../tokenizer/token.h"
int ft_system(t_token *tokens, int *status);
// int ft_chdir(char *command_buf);
void ft_signals(void);
void waitline();
t_token *search_path(t_token *tokens);

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

int ft_system(t_token *tokens, int *status);
// int ft_chdir(char *command_buf);
t_token *search_path(t_token *tokens);
int ft_chdir(char **command_buf, t_env **env);
void ft_signals(void);
void waitline();

t_env *map_new(void);
char *get_env_name(char *ret, char *env);
char *get_env_value(char *ret, char *env);
void envmap_init(t_env **map);
int set_env(t_env **env_head, char *name, char *value);
t_env *item_new(t_env *new_env, char *name, char *value);
void add_new(t_env **map, t_env *new_env);
void env_unset(t_env **env_head, char *delete_env_key);
char *map_get(t_env **env_head, char *name);
void ft_env(t_env **env_head, char *arg);
int ft_chdir(char **command_buf, t_env **env);

#endif
