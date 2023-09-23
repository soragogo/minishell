#include "token.h"
#include "parser.h"
#include <stdbool.h>
#include <libc.h>

int count_commandset(t_token *tokens)
{
	int i = 0;
	int count = 0;
	if (tokens[0].arg != NULL)
		count++;
	while (tokens[i].arg != NULL)
	{
		if (tokens[i].type == PIPE)
			count++;
		i++;
	}
	return count;
}

// void connect_tokens(t_token *tokens)
// {
// 	int i = 0;
// 	while (tokens[i].arg != NULL)
// 	{
// 		if (tokens[i].type == PIPE)
// 		{
// 			tokens[i].next_token = NULL;
// 		}
// 		else if (tokens[i + 1].type == PIPE || tokens[i + 1].arg == NULL)
// 		{
// 			tokens[i].next_token = NULL;
// 		}
// 		else
// 		{
// 			tokens[i].next_token = &tokens[i + 1];
// 		}
// 		i++;
// 	}
// }

void categorize_tokens(t_token *tokens)
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
		else if (i == 0 || (command_flag == 0 && i != 0 && (tokens[i - 1].type < REDIRECT_OUT || tokens[i - 1].type > HERE_DOCUMENT)))
		{
			tokens[i].type = COMMAND;
			command_flag = 1;
		}
		else
			tokens[i].type = FILE_NAME;

		i++;
	}
}

t_commandset *create_command_pipeline(t_token *tokens, int num_of_commands)
{
	t_commandset *commandsets;
	// int num_of_commmands = count_commandset(tokens);
	// int i = 1;
	// int j = 1;

	// connect_tokens(tokens);
	commandsets = malloc(sizeof(t_commandset) * num_of_commands);

	int i = 1;
	commandsets[0].prev = NULL;
	if (num_of_commands > 1)
		commandsets[0].next = &commandsets[1];
	while (i < num_of_commands - 1)
	{
		commandsets[i].next = &commandsets[i + 1];
		commandsets[i].prev = &commandsets[i - 1];
		i++;
	}
	commandsets[num_of_commands - 1].next = NULL;
	if (num_of_commands > 1)
		commandsets[num_of_commands - 1].prev = &commandsets[num_of_commands - 2];
	i = 0;
	while (commandsets[i].next != NULL)
	{
		i++;
	}
	printf("commandset の長さ: %d\n", i + 1);
	// commandsets[0].command = &tokens[0];

	// while (tokens[i].arg != NULL)
	// {
	// 	if (tokens[i - 1].next_token == NULL && tokens[i].type != PIPE)
	// 	{
	// 		commandsets[j].command = &tokens[i];
	// 		j++;
	// 	}
	// 	i++;
	// }
	// commandsets[j].command = NULL;
	return commandsets;
}

int count_command(t_token *tokens)
{
	int i = 0;
	int count = 0;

	while (tokens[i].arg != NULL && tokens[i].type != PIPE)
	{
		if (tokens[i].type == COMMAND || tokens[i].type == COMMAND_OPTION)
			count++;
		i++;
	}
	return count;
}

void import_command(t_token *tokens, t_commandset *commandsets, int num_of_commands)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int count = 0;
	// printf("numofcommands: %d\n",num_of_commands);
	while (i < num_of_commands)
	{
		count = count_command(tokens);
		commandsets[i].command = malloc(sizeof(char *)* (count + 1));

		while (tokens[j].arg != NULL && tokens[j].type != PIPE)
		{
			if (tokens[j].type == COMMAND || tokens[j].type == COMMAND_OPTION)
			{
				commandsets[i].command[k] = tokens[j].arg;
				k++;
			}
			j++;
		}
		commandsets[i].command[k] = NULL;
		k = 0;
		if (tokens[j].type == PIPE)
			j++;
		// for (int a = 0; commandsets[i].command[a] != NULL; a++)
		// {
		// 	printf("command[%d]: %s\n", a, commandsets[i].command[a]);
		// }
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

// void test_parser(char *command)
// {
// 	t_token *result;
// 	t_command *commands;
// 	result = ft_tokenizer(command);
// 	ft_parser(result);
// 	commands = create_command_pipeline(result);

// 	for (int i = 0; commands[i].command != NULL; i++)
// 	{
// 		printf("commands[%d].command->arg = [%s]\n", i, commands[i].command->arg);
// 	}
// 	puts("--------------------------------");
// 	for (int i = 0; result[i].arg != NULL; i++)
// 	{
// 		printf("arg: %-20s / ", result[i].arg);
// 		printf("type: [%s]\n", TYPE_STRINGS[result[i].type]);
// 		if (result[i].is_freed != 1)
// 		{
// 			free(result[i].arg);
// 			result[i].is_freed = 1;
// 		}
// 	}
// 	printf("\n");
// 	free(result);
// 	free(commands);
// }


#include <libc.h>
int main()
{
	t_token *tokens;
	t_commandset *commandsets;
	int num_of_commands;
	char *buff;
	char **cmd;
	while (1)
	{
		buff = readline("test here> ");
		tokens = ft_tokenizer(buff);
		categorize_tokens(tokens);
		num_of_commands = count_commandset(tokens);
		printf("num_of_commands: [%d]\n", num_of_commands);
		commandsets = create_command_pipeline(tokens, num_of_commands);
		import_command(tokens, commandsets, num_of_commands);
		for (int i = 0; i < 2; i++)
		{
			cmd = commandsets[i].command;
			while(*cmd)
			{
				printf("%s\n", *cmd);
				cmd++;
			}

		}
		// test_parser(buff);
		// for (int i = 0; tokens[i].arg != NULL; i++)
		// {
		// 	printf("arg: [%s]\n", tokens[i].arg);
		// 	printf("type: [%d]\n", tokens[i].type);
		// }
		free(buff);
	}
}
