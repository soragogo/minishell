#include "token.h"
#include <stdbool.h>

<<<<<<< HEAD char *quoted_arg(int *num_of_args, char *command, char quote)
{
	char *tmp;

	tmp = command;
	tmp++;
	*num_of_args += 1;
	while (*tmp && *tmp != quote)
=======
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
>>>>>>> eff83dc84bff65363c4fe8b40e91889e41f91d14
			tmp++;
		tmp++;
		return (tmp);
	}

<<<<<<< HEAD
	bool is_separator(char c)
	{
		return (c && c != ' ' && c != '\'' && c != '\"' && c != '|');
	}

	void count_tokens(char *command, int *num_of_args)
	{
=======
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
>>>>>>> eff83dc84bff65363c4fe8b40e91889e41f91d14
		while (*command)
		{
			while (*command == ' ')
				command++;
<<<<<<< HEAD
			if (*command == 34 || *command == 39)
				command = quoted_arg(num_of_args, command, *command);
			else if (*command == '|')
			{
				*num_of_args += 1;
				command++;
			}
			else
			{
				if (*command != ' ' && *command)
				{
					*num_of_args += 1;
					command++;
					while (is_separator(*command))
						command++;
				}
			}
		}
	}

	char *tokenize_nonexpandable(t_token * tokens, char *command)
	{
		int i;
		char *tmp;

		i = 0;
		tmp = command;
		tokens->type = NON_EXPANDABLE;
		tmp++;
		while (tmp[i] && tmp[i] != 39)
			i++;
		tokens->arg = malloc(sizeof(char) * (i + 1));
		i = 0;
		while (*tmp && *tmp != 39)
		{
			tokens->arg[i] = *tmp;
			tmp++;
			i++;
		}
		tokens->arg[i] = '\0';
		tmp++;
		return (tmp);
	}

	char *tokenize_quoted(t_token * tokens, char *command)
	{
		int i;
		char *tmp;

		i = 0;
		tmp = command;
		tokens->type = EXPANDABLE_QUOTED;
		tmp++;
		while (tmp[i] && tmp[i] != 34)
			i++;
		tokens->arg = malloc(sizeof(char) * (i + 1));
		i = 0;
		while (*tmp && *tmp != 34)
		{
			tokens->arg[i] = *tmp;
			tmp++;
			i++;
		}
		tokens->arg[i] = '\0';
		tmp++;
		return (tmp);
	}

	char *tokenize_pipe(t_token * tokens, char *command)
	{
		char *tmp;

		tmp = command;
		tmp++;
		tokens->type = PIPE;
		tokens->arg = malloc(sizeof(char) * 2);
		tokens->arg[0] = '|';
		tokens->arg[1] = '\0';
		return (tmp);
	}

	char *tokenize_expandable(t_token * tokens, char *command)
	{
		int i;
		char *tmp;

		i = 0;
		tmp = command;
		tokens->type = EXPANDABLE;
		while (tmp[i] && tmp[i] != ' ')
			i++;
		tokens->arg = malloc(sizeof(char) * (i + 1));
		i = 0;
		while (*tmp && *tmp != ' ' && *tmp != '|' && *tmp != '\'' && *tmp != '\"')
		{
			tokens->arg[i] = *tmp;
			i++;
			tmp++;
		}
		tokens->arg[i] = '\0';
		// printf("arg: [%s]\n", tokens->arg);
		return (tmp);
=======
			if (*command)
				count++;
			command = find_end_of_arg(command);
			command++;
		}
		return (count);
>>>>>>> eff83dc84bff65363c4fe8b40e91889e41f91d14
	}

	void ft_split(t_token * tokens, char *command, int num_of_tokens)
	{
<<<<<<< HEAD
		int i;

		i = 0;
		// printf("num_of_tokens: %d\n", num_of_tokens);
		while (i < num_of_tokens)
		{
			while (*command == ' ')
				command++;
			if (*command == 39)
				command = tokenize_nonexpandable(&tokens[i], command);
			else if (*command == 34)
				command = tokenize_quoted(&tokens[i], command);
			else if (*command == '|')
				command = tokenize_pipe(&tokens[i], command);
			else
				command = tokenize_expandable(&tokens[i], command);
			// printf("command :[%s]\n", command);
			i++;
		}
		// printf("tokens :%d\n", i);
=======
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
>>>>>>> eff83dc84bff65363c4fe8b40e91889e41f91d14
		tokens[i].arg = NULL;
	}

	t_token *ft_tokenizer(char *command)
	{
		int num_of_tokens;
		t_token *tokens;

<<<<<<< HEAD
		num_of_tokens = 0;
		count_tokens(command, &num_of_tokens);
		tokens = (t_token *)malloc(sizeof(t_token) * (num_of_tokens + 1));
		ft_split(tokens, command, num_of_tokens);
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
		num_of_tokens = count_tokens(command);
		tokens = (t_token *)malloc(sizeof(t_token) * (num_of_tokens + 1));
		if (!tokens)
			return (NULL);
		ft_split(tokens, command, num_of_tokens);
>>>>>>> eff83dc84bff65363c4fe8b40e91889e41f91d14
		return (tokens);
	}

	// #include <libc.h>
	// int main()
	// {
<<<<<<< HEAD
=======
	// 	t_token *result;
>>>>>>> eff83dc84bff65363c4fe8b40e91889e41f91d14
	// 	char *command;
	// 	while (1)
	// 	{
	// 		command = readline("test here> ");
<<<<<<< HEAD
	// 		ft_tokenizer(command);
	// 		free(command);
	// 	}

	// 	//	for (int i = 0; result[i] != NULL; i++)
	// 	//	{
	// 	//		printf("arg: [%s]\n", result[i].arg);
	// 	//		printf("type: [%d]\n", result[i].type);
	// 	//	}
=======
	// 		result = ft_tokenizer(command);
	// 		// for (int i = 0; result[i].arg != NULL; i++)
	// 		// {
	// 		// 	printf("arg: [%s]\n", result[i].arg);
	// 		// 	printf("type: [%d]\n", result[i].type);
	// 		// }
	// 		free(command);
	// 	}
>>>>>>> eff83dc84bff65363c4fe8b40e91889e41f91d14
	// }
