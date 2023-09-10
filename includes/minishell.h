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


typedef struct	s_env			//環境変数のリスト
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_info
{
	t_env	*map_head;			//環境変数のリスト
	int		exit_status_log;	//直前のコマンドの終了ステータス
}	t_info;

// int ft_system(char *command, int *status);
// int ft_chdir(char *command_buf);
void ft_signals(void);
void waitline();

	/* env function */
t_env	*map_new(void);
char	*get_env_name(char *ret, char *env);
char	*get_env_value(char *ret, char *env);
void	envmap_init(t_env **map);
int		set_env(t_env **env_head, char *name, char *value);
t_env	*item_new(t_env *new_env, char *name, char *value);
void	add_new(t_env **map, t_env *new_env);
void	env_unset(t_env **env_head, char *delete_env_key);
char	*map_get(t_env **env_head, char *name);
void	free_map(t_env **map);

	/* builtin command */
int	ft_echo(t_token *tokens, int status);
int	ft_chdir(t_token *tokens, t_env **env);
int	ft_pwd(void);
int	ft_exit(char **arg);
int	ft_unset(t_env **env_head, t_token *tokens);
int	ft_env(t_env **env_head);
int	ft_export(t_env **map, t_token *tokens);

	/* utils */
int is_builtin(t_token *tokens, t_info *info);

#endif
