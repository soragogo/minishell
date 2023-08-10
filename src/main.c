#include "minishell.h"

int main()
{
	char *command_buf;
	int status;

	while (1)
	{
		command_buf = readline("minishell> ");
		add_history(command_buf);
		ft_system(command_buf, &status);
		free(command_buf);
	}
	return (0);
}
__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}
