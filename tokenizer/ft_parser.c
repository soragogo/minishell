/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:38:41 by ekamada           #+#    #+#             */
/*   Updated: 2023/09/30 21:48:38 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	commandsets = ft_calloc(num_of_commands, sizeof(t_commandset));

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
		i++;
	return commandsets;
}

int count_command(t_token *tokens)
{
	int i = 0;
	int count = 0;

	while (tokens[i].arg != NULL && tokens[i].type != PIPE)
	{
		if (tokens[i].type == COMMAND || tokens[i].type == COMMAND_OPTION || tokens[i].type == FILE_NAME)
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
		commandsets[i].command = ft_calloc(count + 1, sizeof(char *));

		while (tokens[j].arg != NULL && tokens[j].type != PIPE)
		{
			if (tokens[j].type == COMMAND || tokens[j].type == COMMAND_OPTION || tokens[j].type == FILE_NAME)
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
		i++;
	}
}

// void ft_parser(char *buff)
t_commandset *ft_parser(char *buff)
{
	t_token *tokens;
	t_commandset *commandsets;
	int num_of_commands;

	tokens = ft_tokenizer(buff);
	categorize_tokens(tokens);
	num_of_commands = count_commandset(tokens);
	printf("num_of_commands: [%d]\n", num_of_commands);
	commandsets = create_command_pipeline(tokens, num_of_commands);
	import_command(tokens, commandsets, num_of_commands);
	import_redirection(tokens, commandsets, num_of_commands);
	test_commandsets(commandsets, num_of_commands);
	return (commandsets);
}

// #include "token.h"
// #include <stdio.h>
// #include <libc.h>
// int main()
// {

// 	char *buff;
// 	while (1)
// 	{
// 		buff = readline("test here> ");
// 		ft_parser(buff);
// 		free(buff);
// 	}
// }
