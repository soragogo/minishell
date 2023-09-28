#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

//コマンドがbuiltinかを確かめる関数
int is_builtin(t_commandset *command){
	const char *builtin[] = {"cd", "pwd", "export", "unset", "env", "exit", NULL};
	int i = 0;

	while (builtin[i] != NULL)
	{
		if (strcmp(*command[0].command, builtin[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

//builtinコマンドを実行する関数
int exec_builtin(t_commandset *commands, t_info *info)
{
	int status;

	status = 0;
	//後でredirectの処理を書く

	// if (strcmp(commands[0].command->arg, "echo") == 0)
	// 	status = ft_echo(commands[0], info->exit_status_log);
	// else if (strcmp(commands[0].command->arg, "cd") == 0)
	// 	status = ft_chdir(commands[0], &(info->map_head));
	// else 
	if (strcmp(*commands[0].command, "env") == 0)
		status = ft_env(&(info->map_head));
	else if (strcmp(*commands[0].command, "pwd") == 0)
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

void handle_pipe(int left_pipe[2], int right_pipe[2], t_commandset *command)
{
	if (command->prev)
	{
		//コマンドの入力をパイプから受け取る
		dup2(left_pipe[0], STDIN_FILENO);
		close(left_pipe[1]);
		close(left_pipe[0]);
	}
	if (command->next)
	{
		//コマンドの出力先をパイプに変更
		dup2(right_pipe[1], STDOUT_FILENO);
		close(right_pipe[0]);
		close(right_pipe[1]);
	}
}

void create_pipe(t_commandset *command, int new_pipe[2]){
	if (command->next){
		if (pipe(new_pipe) < 0)
			printf("pipe error");
	}
}

int exec_command(t_commandset *commands, t_info *info){
	int status;
	static int new_pipe[2];
	static int old_pipe[2];
	char *path;
	char **my_environ;
	pid_t pid;

	status = 0;
	create_pipe(commands, new_pipe);
	my_environ = create_environ(&(info->map_head));
	if ((pid = fork()) < 0)
		return (-1);
	else if (pid == 0){//子プロセス
	// pid = 0;
	// if (pid == pid){//子プロセス
		printf("子プロセス\n");
		handle_pipe(old_pipe, new_pipe, commands);
		// do_redirect(commands->node);
		if (is_builtin(commands) != -1)
		{
			// write(1, "builtin\n", 8);
			status = exec_builtin(commands, info);
		}
		else
		{
			// write(1, "not builtin\n", 12);
			printf("%s\n", *commands->command);
			// path = malloc(sizeof(char) * PATH_MAX);
			path = fetch_path(*commands->command, &(info->map_head));//path作るの失敗してる
			printf("path: [%s]\n", path);
			status = execve(path, commands->command, my_environ);
			if (status == -1)
				perror("execve");
		}
	}
	old_pipe[0] = new_pipe[0];
	old_pipe[1] = new_pipe[1];
    close(new_pipe[0]);
    close(new_pipe[1]);
	commands->pid = pid;
	printf("pid: %d\n", pid);
	return (status);
}

void wait_command(t_commandset *commands){
	int status;
	printf("wait_command: %d\n", commands->pid);
	if (waitpid(commands->pid, &status, 0) < 0)
		printf("waitpid error\n");
}


int handle_command(t_commandset *commands, t_info *info){
	int status;

	status = 0;
	//pipeなし
	if (commands[1].command == NULL && is_builtin(commands) != -1)//fork()いらない
	{
		status = exec_builtin(commands, info);
	}
	else//fork()必要
	{
		while (commands != NULL)
		{
			status = exec_command(commands, info);
			wait_command(commands);
			printf("wait抜けた\n");
			commands = commands->next;
		}
	}
	return (status);
}


/* --------------------------------------------------------- */


#include "../includes/minishell.h"
#include "../tokenizer/token.h"
#include "../tokenizer/parser.h"

int main() {
    t_commandset commands[2];
    
    // コマンド1
    commands[0].command = malloc(sizeof(char *) * 1);
	commands[0].command[0] = "cat";
	commands[0].command[1] = "a.txt";
	commands[0].node = (t_redirect *)malloc(sizeof(t_redirect));
	commands[0].node->oldfd = 1;
    // commands[0].command = {"cat", "a.out"};
	commands[0].next = &commands[1];
	// commands[0].next = NULL;
	commands[0].prev = NULL;
    
    // コマンド2
    commands[1].command = malloc(sizeof(char *) * 1);
	commands[1].command[0] = "wc";
	// commands[1].command[1] = "a";
	// commands[1].command[0] = "cat";
	// commands[1].command[1] = "a.txt";
	commands[1].node = (t_redirect *)malloc(sizeof(t_redirect));
	commands[1].node->oldfd = 1;
    // commands[0].command = {"cat", "a.out"}; // 実行したいコマンドのパスを指定します。
	commands[1].next = NULL;
	commands[1].prev = &commands[0];
    // コマンドを実行
    t_env *map;
	map = map_new();
    envmap_init(&map);
	t_info info;
	info.map_head = map;
    int status = handle_command(commands, &info);

    if (status == -1) {
        printf("コマンドの実行に失敗しました。\n");
    } else {
        printf("コマンドの実行が正常に完了しました。終了コード: %d\n", status);
    }

    free(commands[0].command);
    free(commands[1].command);

    return 0;
}


