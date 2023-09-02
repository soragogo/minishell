#include "../includes/minishell.h"

//builtinコマンドかの確認
//そうだったらそのまま実行
//違ったらパスを探して実行
//まずパースから？

//'|'があったらパイプ処理 TYPE 2がパイプ
//pipe()

//コマンドがbuiltinかを確かめる関数
void is_builtin(char *argv){
	if (strcmp(argv, "echo") == 0)
		ft_echo(argv);
	else if (strcmp(argv, "cd") == 0)
		ft_cd(argv);
	else if (strcmp(argv, "pwd") == 0)
		ft_pwd();
	else if (strcmp(argv, "export") == 0)
		ft_export(argv);
	else if (strcmp(argv, "unset") == 0)
		ft_unset(argv);
	else if (strcmp(argv, "env") == 0)
		ft_env();
	else if (strcmp(argv, "exit") == 0)
		ft_exit(argv);
	else
		ft_execve(argv);
}

ft_execve(char **argv){
	char *path;
	char *tmp;
	char **paths;
	int i;

	i = 0;
	path = getenv("PATH");
	paths = ft_split(path, ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, argv[0]);
		if (access(tmp, F_OK) == 0)
		{
			execve(tmp, argv, NULL);
			perror("execve");
			exit(1);
		}
		i++;
	}
	perror("command not found");
	exit(1);
}

// int run_pipe(char **argv1, char **argv2){
// 	int fd[2];
// 	pid_t pid;
// 	int status;
	

// 	pipe(fd);
// 	pid = fork();
// 	if (pid == 0)//子プロセス
// 	{
// 		dup2(fd[1], 1);
// 		close(fd[0]);
// 		if (strcmp(argv1[0], "cd") == 0)
// 			execve("")
// 		execvp(argv1[0], argv1);
// 		perror("execvp");
// 		exit(1);
// 	}
// 	else if (pid > 0)//親プロセス
// 	{
// 		dup2(fd[0], 0);
// 		close(fd[1]);
// 		execvp(argv2[0], argv2);
// 		perror("execvp");
// 		exit(1);
// 	}
// 	else
// 	{
// 		perror("fork");
// 		exit(1);
// 	}
// 	return (0);
// }

int count_args(char **argv){
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void run_pipe(char **argv){
	int i;
	int clunt;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (strcmp(argv[i], "|") == 0)
			count++;
		i++;
	}
	return (i);
}



int main (){
	char *argv1[] = {"echo", "-n", NULL};
	char *argv2[] = {"grep", "pipe", NULL};

	run_pipe(argv1, argv2);
	return (0);
}