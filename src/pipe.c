#include "../includes/minishell.h"

//コマンドがbuiltinかを確かめる関数
int is_builtin(t_token *tokens, t_info *info){
	int status;

	status = 0;
	if (strncmp(tokens[0].arg, "echo", 4) == 0 && ft_strlen(tokens[0].arg) == 4)
		status = ft_echo(tokens, info->exit_status_log);
	else if (strcmp(tokens[0].arg, "cd") == 0)
		status = ft_chdir(tokens, &(info->map_head));
	else if (strcmp(tokens[0].arg, "env") == 0)
		status = ft_env(&(info->map_head));
	else if (strcmp(tokens[0].arg, "pwd") == 0)
		status = ft_pwd();
	else if (strcmp(tokens[0].arg, "export") == 0)
		status = ft_export(&info->map_head, tokens);
	else if (strcmp(tokens[0].arg, "unset") == 0)
		status = ft_unset(&info->map_head, tokens);
	// else if (strcmp(tokens[0].arg, "exit") == 0)
	// 	status = ft_exit(&argv);
	else
		return (-1);
	return (status);
}

int exec_command(t_token *tokens, t_info *info){
	
}

void handle_redirect(){
	
}

// void ft_execve(char **argv){
// 	char *path;
// 	char *tmp;
// 	char **paths;
// 	int i;

// 	i = 0;
// 	path = getenv("PATH");
// 	paths = ft_split(path, ':');
// 	while (paths[i])
// 	{
// 		tmp = ft_strjoin(paths[i], "/");
// 		tmp = ft_strjoin(tmp, argv[0]);
// 		if (access(tmp, F_OK) == 0)
// 		{
// 			execve(tmp, argv, NULL);
// 			perror("execve");
// 			return ;
// 			// exit(1);
// 		}
// 		i++;
// 	}
// 	// perror("command not found");
// 	// exit(1);
// }

// int count_pipe(char **argv){
// 	int i;
// 	int count;

// 	count = 0;
// 	i = 0;
// 	while (argv[i])
// 	{
// 		if (strcmp(argv[i], "|") == 0)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }
