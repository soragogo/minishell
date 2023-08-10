#include "minishell.h"

int ft_system(char *command, int *status)
{
	pid_t pid;
	char *commands[] = {"bash", "-c", command, NULL};

	pid = fork();

	if (pid == 0)
	{
		execv("/bin/sh", commands);
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
	}
	else
		return (-1);
	return WIFEXITED(status);
}
