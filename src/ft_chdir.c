#include "minishell.h"

int ft_chdir(char *command_buf)
{
	if (command_buf[2] == '\0')
	{
		const char *home = getenv("HOME");
		if (home)
			chdir(home);
	}
	else
	{
		char *dir_path = strchr(command_buf, ' ');
		if (dir_path)
		{
			dir_path++;
			if (chdir(dir_path) != 0)
			{	
				printf("cd: no such file or directory: %s\n", dir_path);
				return (1);
			}
		}
	}
	return (0);

}