#include "token.h"
#include <stdbool.h>

int is_dilimeter(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return 1;
	return 0;
}

char *find_end_of_quote(char *command)
{
	char *tmp = command;
	char c = *command;

	tmp++;
	while (*tmp && *tmp != c)
		tmp++;
	tmp++;
	return (tmp);
}

char *find_end_of_arg(char *command)
{
	char *tmp = command;
	if (is_dilimeter(*tmp) == 1)
	{
		if (*tmp == '<' && *(tmp + 1) == '<')
			tmp++;
		else if (*tmp == '>' && *(tmp + 1) == '>')
			tmp++;
		return tmp;
	}
	else
	{
		while (is_dilimeter(*command) == 0 && *command != ' ' && *command)
		{
			if (*command == '\'' || *command == '\"')
				command = find_end_of_quote(command);
			else if (*command)
				command++;
		}
		command--;
		return (command);
	}
}

int count_tokens(char *command)
{
	int count;

	count = 0;
	while (*command)
	{
		while (*command == ' ')
			command++;
		if (*command)
			count++;
		command = find_end_of_arg(command);
		command++;
	}
	return (count);
}

void ft_token_split(t_token *tokens, char *command, int num_of_tokens)
{
	char *start;
	char *end;
	int i;

	i = 0;
	start = command;
	while (*start == ' ')
		start++;
	end = find_end_of_arg(command);
	while (i < num_of_tokens)
	{
		tokens[i].arg = malloc(sizeof(char) * (end - start + 2));
		tokens[i].is_freed = 0;
		strlcpy(tokens[i].arg, start, end - start + 2);
		start = end + 1;
		while (*start == ' ')
			start++;
		if (*start)
			end = find_end_of_arg(start);
		i++;
	}
	tokens[i].arg = NULL;
}

t_token *ft_tokenizer(char *command)
{
	int num_of_tokens;
	t_token *tokens;

	num_of_tokens = count_tokens(command);
	tokens = (t_token *)malloc(sizeof(t_token) * (num_of_tokens + 1));
<<<<<<< HEAD
	ft_token_split(tokens, command, num_of_tokens);
	// printf("num_of_tokens: [%d]\n", num_of_tokens);
	// for (int i = 0; tokens[i].arg != NULL; i++)
	// {
	// 	puts("------------------");
	// 	printf("token[%d] :[%s]\n", i, tokens[i].arg);
	// 	if (tokens[i].type == 0)
	// 		puts("NON_EXPANDABLE ''");
	// 	if (tokens[i].type == 1)
	// 		puts("EXPANDABLE_QUOTED "
	// 			 "");
	// 	if (tokens[i].type == 2)
	// 		puts("PIPE |");
	// 	if (tokens[i].type == 3)
	// 		puts("EXPANDABLE 文字列");
	// }
=======
	if (!tokens)
		return (NULL);
	ft_split(tokens, command, num_of_tokens);
>>>>>>> ffd562c95b262524d0e74e84217e6a8f6d89be3e
	return (tokens);
}

// #include <libc.h>
// int main()
// {
// 	t_token *result;
// 	char *command;
// 	while (1)
// 	{
// 		command = readline("test here> ");
// 		result = ft_tokenizer(command);
<<<<<<< HEAD
// 		for (int i = 0; result[i].arg != NULL; i++)
// 		{
// 			printf("arg: [%s]\n", result[i].arg);
// 			printf("type: [%d]\n", result[i].type);
// 		}
=======
// 		// for (int i = 0; result[i].arg != NULL; i++)
// 		// {
// 		// 	printf("arg: [%s]\n", result[i].arg);
// 		// 	printf("type: [%d]\n", result[i].type);
// 		// }
>>>>>>> ffd562c95b262524d0e74e84217e6a8f6d89be3e
// 		free(command);
// 	}
// }
