#include "../includes/minishell.h"

int builtin_pwd(char *command_buf)
{
	char *envp;
	
	// envp = getenv("PWD");
	(void)command_buf;
	envp = getcwd(NULL, 0);
	if (!envp)
	{
		printf("error: getcwd");
		return (1);
	}//ここはあとで
	printf("%s\n", envp);
	free (envp);
	return (0);
}

// int main(){
// 	char *command_buf = "pwd";
// 	builtin_pwd(command_buf);
// 	return (0);
// }

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
