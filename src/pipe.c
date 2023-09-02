#include "../includes/minishell.h"

//builtinコマンドかの確認
//そうだったらそのまま実行
//違ったらパスを探して実行
//まずパースから？

//'|'があったらパイプ処理
//pipe()

int run_pipe(char **argv1, char **argv2){
	int fd[2];
	pid_t pid;
	int status;
	

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		if (strcmp(argv1[0], "cd") == 0)
			execve("")
		execvp(argv1[0], argv1);
		perror("execvp");
		exit(1);
	}
	else if (pid > 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		execvp(argv2[0], argv2);
		perror("execvp");
		exit(1);
	}
	else
	{
		perror("fork");
		exit(1);
	}
	return (0);
}

int main (){
	char *argv1[] = {"ls", "-al", NULL};
	char *argv2[] = {"grep", "pipe", NULL};

	run_pipe(argv1, argv2);
	return (0);
}