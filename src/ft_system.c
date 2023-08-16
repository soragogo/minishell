#include "minishell.h"


int ft_system(char *command, int *status)
{
	pid_t pid;
	char *commands[] = {"bash", "-c", command, NULL};
	extern char **environ;

	pid = fork();

	if (pid == 0)
	{
		execve("/bin/sh", commands, environ);
	}
	else if (pid > 0)
	{
		do
		{
			if (waitpid(pid, status, 0) == -1)
			{
				return -1;
			}
		} while (!WIFEXITED(*status) && !WIFSIGNALED(*status));
		*status = WEXITSTATUS(*status);
	}
	else
		return (-1);
	return WIFEXITED(status);
}
