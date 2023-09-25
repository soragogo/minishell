#include "token.h"
#include "parser.h"
#include <stdbool.h>
#include <libc.h>

int count_redirection(t_token *tokens)
{
	int i = 0;
	int count = 0;

	while (tokens[i].arg != NULL && tokens[i].type != PIPE)
	{
		if (tokens[i].type >= REDIRECT_OUT && tokens[i].type <= HERE_DOCUMENT)
			count++;
		i++;
	}
	return count;
}

void connect_redirections(t_redirect *node, int count)
{
	int i = 0;
	while (i < count)
	{

		i++;
	}
}

void import_redirection(t_token *tokens, t_commandset *commandsets, int num_of_commands)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int count = 0;

	while (i < num_of_commands)
	{
		count = count_redirection(tokens);
		commandsets[i].node = malloc(sizeof(char *) * (count));
		connect_redirections(commandsets[i].node, count);
		while (tokens[j].arg != NULL && tokens[j].type != PIPE)
		{
			if (tokens[j].type >= REDIRECT_OUT && tokens[j].type <= HERE_DOCUMENT)
			{
				if (tokens[j + 1].type == FILE_NAME)
					commandsets[i].node[k].filename = tokens[j + 1].arg;
				k++;
			}
			j++;
		}
		k = 0;
		if (tokens[j].type == PIPE)
			j++;
		i++;
	}
}
