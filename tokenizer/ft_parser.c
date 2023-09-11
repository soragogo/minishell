#include "token.h"
#include <stdbool.h>

void ft_parser(t_token *tokens)
{
	int i = 0;
	int command_flag = 0;
	while (tokens[i].arg != NULL)
	{
		if (strncmp(tokens[i].arg, "|", 2) == 0)
		{
			tokens[i].type = PIPE;
			command_flag = 0;
		}
		else if (strncmp(tokens[i].arg, ">", 2) == 0)
			tokens[i].type = REDIRECT_OUT;
		else if (strncmp(tokens[i].arg, "<", 2) == 0)
			tokens[i].type = REDIRECT_IN;
		else if (strncmp(tokens[i].arg, ">>", 3) == 0)
			tokens[i].type = APPEND_OUT;
		else if (strncmp(tokens[i].arg, "<<", 3) == 0)
			tokens[i].type = HERE_DOCUMENT;
		else if (tokens[i].arg[0] == '-' && command_flag == 1)
			tokens[i].type = COMMAND_OPTION;
		else if (i == 0 || command_flag == 0)
		{
			tokens[i].type = COMMAND;
			command_flag = 1;
		}
		else
			tokens[i].type = FILE_NAME;

		i++;
	}
}

////////////////////////////ここからテスト関数など/////////////////////////////////

#include "token.h"
#include <stdio.h>

const char *TYPE_STRINGS[] = {
	"UNCATEGORIZED",
	"PIPE",			 // | (パイプ)
	"REDIRECT_OUT",	 // > (リダイレクト出力)
	"REDIRECT_IN",	 // < (リダイレクト入力)
	"APPEND_OUT",	 // >> (出力の追加)
	"HERE_DOCUMENT", // << (ヒアドキュメント)
	"COMMAND",
	"COMMAND_OPTION",
	"FILE_NAME"};

void test_parser(char *command)
{
	t_token *result;
	result = ft_tokenizer(command);
	ft_parser(result);
	for (int i = 0; result[i].arg != NULL; i++)
	{
		printf("arg: %-20s / ", result[i].arg);
		printf("type: [%s]\n", TYPE_STRINGS[result[i].type]);
		if (result[i].is_freed != 1)
		{
			free(result[i].arg);
			result[i].is_freed = 1;
		}
	}
	printf("\n");
	free(result);
}

#include <libc.h>
int main()
{
	t_token *result;
	char *command;
	while (1)
	{
		command = readline("test here> ");
		// result = ft_tokenizer(command);
		// ft_parser(result);
		test_parser(command);
		// for (int i = 0; result[i].arg != NULL; i++)
		// {
		// 	printf("arg: [%s]\n", result[i].arg);
		// 	printf("type: [%d]\n", result[i].type);
		// }
		free(command);
	}
}
