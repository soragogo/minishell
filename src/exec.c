#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"


typedef enum e_pipe_state{
	NO_PIPE,
	PIPE_READ_ONLY,
	PIPE_WRITE_ONLY,
	PIPE_READ_WRITE
}	t_pipe_state;

//コマンドがbuiltinかを確かめる関数
int is_builtin(t_command *command){
	const char *builtin[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int i = 0;

	while (builtin[i] != NULL)
	{
		if (strcmp(command[0].command->arg, builtin[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

//builtinコマンドを実行する関数
int exec_builtin(t_command *commands, t_info *info)
{
	int status;

	status = 0;
	// if (strcmp(commands[0].command->arg, "echo") == 0)
	// 	status = ft_echo(commands[0], info->exit_status_log);
	// else if (strcmp(commands[0].command->arg, "cd") == 0)
	// 	status = ft_chdir(commands[0], &(info->map_head));
	// else 
	if (strcmp(commands[0].command->arg, "env") == 0)
		status = ft_env(&(info->map_head));
	else if (strcmp(commands[0].command->arg, "pwd") == 0)
		status = ft_pwd();
	// else if (strcmp(commands[0].command->arg, "export") == 0)
	// 	status = ft_export(&info->map_head, commands[0]);
	// else if (strcmp(commands[0].command->arg, "unset") == 0)
	// 	status = ft_unset(&info->map_head, commands[0]);
	// else if (strcmp(tokens[0].arg, "exit") == 0)
	// 	status = ft_exit(&argv);
	else
		return (-1);
	return (status);
}

void dup_pipe(int old_pipe[2], int new_pipe[2], t_pipe_state state)
{
	if (state == PIPE_READ_ONLY)
	{
		close(old_pipe[1]);
		dup2(old_pipe[0], 0);
		close(old_pipe[0]);
	}
	else if (state == PIPE_WRITE_ONLY)
	{
		close(new_pipe[0]);
		dup2(new_pipe[1], 1);
		close(new_pipe[1]);
	}
	else if (state == PIPE_READ_WRITE)
	{
		close(old_pipe[1]);
		dup2(old_pipe[0], 0);
		close(old_pipe[0]);
		close(new_pipe[0]);
		dup2(new_pipe[1], 1);
		close(new_pipe[1]);
	}
}

char *create_path(t_token *command)
{
	char *token_twod[10000];
	int i = 0;

	search_path(command);
	while (command[i].arg != NULL)
	{
		token_twod[i] = command[i].arg;
		i++;
	}
	token_twod[i] = NULL;
	return (token_twod[0]);
}

char **join(char const *s1, char const *s2, char **environ)
{
	// char	*joined;
	int		i;
	int		strslen;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
		// return ;
	strslen = ft_strlen(s1) + ft_strlen(s2);
	environ = (char **)malloc(sizeof(char *) * 1);
	*environ = (char *)malloc(sizeof(char) * (strslen + 1));
	if (environ == NULL)
		// return ;
		return (NULL);
	while (*s1)
		environ[0][i++] = *s1++;
	while (*s2)
		environ[0][i++] = *s2++;
	environ[0][i] = 0;
	return (environ);
}

void env_join(char *name, char *value, char **environ)
{
	environ = join(name, "=", environ);
	environ = join(environ[0], value, environ);
}

char **create_environ(t_env **env_head)
{
	t_env *tmp;
	char **environ;
    // char **ret;
    int i;

    // ret = environ;
    i = 0;
	tmp = *env_head;
	while (tmp)
	{
		// printf("%s=%s\n", tmp->name, tmp->value);
		env_join(tmp->name, tmp->value, &environ[i]);
		i++;
		tmp = tmp->next;
	}
	environ = (char **)malloc(sizeof(char *) * 1);
	environ[i] = (char *)malloc(sizeof(char *) * 1);
    environ[i] = NULL;
	return (environ);
}

int exec_command(t_command *commands, t_info *info){
	int status;
	int new_pipe[2];
	pid_t pid;

	status = 0;
	
	if ((pid = fork()) < 0)
		return (-1);
	else if (pid == 0){//子プロセス
	// pid = 0;
	// if (pid == 0){//子プロセス
		printf("子プロセス\n");
		if (is_builtin(commands) != -1){
			printf("%d\n", is_builtin(commands));
			status = exec_builtin(commands, info);
		}
		else
		{
			printf("通過\n");
			char *path = create_path(commands[0].command);
			char **my_environ = create_environ(&(info->map_head));
			status = execve(path, &commands[0].command->arg, my_environ);
		}
	}
	commands->pid = pid;
	return (status);
}

void wait_command(t_command *command){
	int status;
	int i;

	i = 0;
	while (command[i].command != NULL)
	{
		waitpid(command[i].pid, &status, 0);
		i++;
	}
}

int handle_command(t_command *command, t_info *info){
	int status;

	status = 0;
	//pipeなし
	if (command[1].command == NULL)
	{
		//builtin
		if (is_builtin(command) != -1)
			status = exec_builtin(command, info);
		//外部コマンド
		else
		{
			status = exec_command(command, info);
			wait_command(command);
		}
	}
	else//pipeあり
	{
		// handle_pipe(command, info);
		status = exec_command(command, info);
		wait_command(command);
	}
	return (status);
}


/* --------------------------------------------------------- */


#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

int main() {
    // 仮想のコマンドを作成します。実際のプログラムではユーザーの入力からトークンを生成する必要があります。
    t_command commands[2]; // 仮に2つのコマンドをサポートしているものとします。
    
    // コマンド1
    commands[0].command = (t_token *)malloc(sizeof(t_token));
    commands[0].command->arg = "ls"; // 実行したいコマンドのパスを指定します。
    
    // コマンド2
    commands[1].command = (t_token *)malloc(sizeof(t_token));
    commands[1].command->arg = "/usr/bin/grep"; // 別のコマンドを実行したい場合、ここでパスを指定します。

    // コマンドを実行
    t_env *map; // 未定義の t_info 構造体を仮定します。
	map = map_new();
    envmap_init(&map);
	t_info info;
	info.map_head = map;
    int status = handle_command(commands, &info);

    // コマンドの実行結果をチェック
    if (status == -1) {
        printf("コマンドの実行に失敗しました。\n");
    } else {
        printf("コマンドの実行が正常に完了しました。終了コード: %d\n", status);
    }

    // メモリの解放を忘れずに
    free(commands[0].command);
    free(commands[1].command);

    return 0;
}
