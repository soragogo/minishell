#include "token.h"
#include "parser.h"
#include <stdbool.h>
#include <libc.h>


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


void test_commandsets(t_commandset *commandsets, int num_of_commands)
{
	char **cmd;

	for (int i = 0; i < num_of_commands; i++)
	{
		cmd = commandsets[i].command;
		while (*cmd)
		{
			printf("%s\n", *cmd);
			cmd++;
		}
		puts("_____________________");
		for (int j = 0; j < 1024; j++)
		{
			printf("redirection_filename: %s\n", commandsets[i].node[j].filename);
			if (commandsets[i].node[j].next == NULL)
			{
				puts("the next is NULL");
				break;
			}
		}
	}
}
