#include "../includes/minishell.h"

void free_before_closing(t_token *tokens, char *command_buf)
{
	for (int i = 0; tokens[i].arg != NULL; i++)
	{
		if (tokens[i].is_freed == 0)
			free(tokens[i].arg);
	}
	free(tokens);
	free(command_buf);
}

char *ft_readline()
{
	char *command_buf;
	command_buf = readline("minishell> ");
	if (command_buf)
		add_history(command_buf);
	return (command_buf);
}

int main()
{
	char *command_buf;
	int status;
	t_token *tokens;
	while (1)
	{
		ft_signals();
		command_buf = ft_readline();
		if (!command_buf)
			break;
		if (*command_buf == '\0')
			continue;
		tokens = ft_tokenizer(command_buf);
		if (ft_strncmp(command_buf, "echo $?", 8) == 0)
		{
			printf("%d\n", status);
			status = 0;
		}
		else
			ft_system(tokens, &status);
		free_before_closing(tokens, command_buf);
	}
	return (0);
}
/*
__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}*/
